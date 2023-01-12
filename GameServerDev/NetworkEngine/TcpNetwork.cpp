#include "pch.h"
#include "TcpNetwork.h"
#include "Session.h"
#include "NetworkEvent.h"
#include "InternalPacketHandler.h"
#include "GamePacketInstaller.h"
#include "Handshake.h"

TcpNetwork::TcpNetwork(ServiceBase& ServiceBase)
	:
	_socket(ServiceBase),
	_connected(false),
	_pending(false),
	_session()
{
}

TcpNetwork::~TcpNetwork()
{
	_socket.Dispose();
}

void TcpNetwork::AttachSession(SessionPtr session)
{
	auto sessionPrev = _session.lock();
	if (sessionPrev)
	{
		sessionPrev->DetachNetwork();
	}

	_session = session;

	if (IsConnected())
	{
		session->AttachNetwork(shared_from_this());
	}
}

void TcpNetwork::RequireHandshake(HandshakePtr handshake)
{
	_handshake = std::move(handshake);
}

void TcpNetwork::Recv(DWORD recvBytes)
{
	static InternalPacketHandler InternalPacketHandler;
	static PacketHandler* GamePacketHandler = GamePacketInstaller::GetHandler();

	if (!_recvBuffer.OnDataRecv(recvBytes))
	{
		DisconnectOnError("recv buffer overflows");
		return;
	}
	
	auto session = _session.lock();
	if (session == nullptr)
	{
		DisconnectOnError("session disposed");
		return;
	}

	while (_recvBuffer.IsHeaderReadable())
	{
		CHAR* bufferToRead = _recvBuffer.GetBufferPtrRead();

		PacketHeader header = PacketHeader::Peek(bufferToRead);

		if (!_recvBuffer.IsReadable(header.size))
		{
			break;
		}

		if (InternalPacketHandler.IsValidProtocol(header.protocol))
		{
			InternalPacketHandler.HandleRecv(shared_from_this(), header, bufferToRead);

			continue;
		}

		SessionPtr session = _session.lock();

		if (GamePacketHandler->IsValidProtocol(header.protocol) && session)
		{
			GamePacketHandler->HandleRecv(session, header, bufferToRead);
		}
		else
		{
			DisconnectOnError("unknown protocol");
			break;
		}
	}

	_recvBuffer.Rotate();
}

void TcpNetwork::SendAsync(const BufferSegment& segment)
{
	_sendBuffer.Pend(segment);
	
	if (_pending.exchange(true) == false)
	{
		Flush();
	}
}

void TcpNetwork::DisconnectAsync()
{
	if (false == _socket.DisconnectAsync(DisconnectEvent(shared_from_this())))
	{
		LOG_ERROR("disconnect failed %s", get_last_err_msg());
	}
}

void TcpNetwork::ConnectAsync(const EndPoint& endPoint, const OnConnectFunc& onConnected, const OnConnectFailFunc& onConnectFailed)
{
	if (NetUtils::SetReuseAddress(_socket.GetSocket(), true) == false)
	{
		LOG_ERROR("connect failed to %s, %s", endPoint.ToString().c_str(), get_last_err_msg());
		return;
	}

	if (NetUtils::BindAnyAddress(_socket.GetSocket(), 0) == false)
	{
		LOG_ERROR("connect failed to %s, %s", endPoint.ToString().c_str(), get_last_err_msg());
		return;
	}

	if (!_socket.ConnectAsync(endPoint, ConnectEvent(shared_from_this(), endPoint, onConnected, onConnectFailed)))
	{
		LOG_ERROR("connect failed to %s, %s", endPoint.ToString().c_str(), get_last_err_msg());
	}
}

void TcpNetwork::Start()
{
	_recvBuffer.Clear();
	_sendBuffer.Clear();
	_pending = false;

	RegisterRecv();
}

void TcpNetwork::Close()
{
	if (_socket.IsOk())
	{
		DisconnectAsync();

		return;
	}

	if (_connected)
	{
		LOG_WARN("closing already errored socket...");

		SetDisconnected();
	}
}

shared_ptr<TcpNetwork> TcpNetwork::Create(ServiceBase& serviceBase)
{
	return make_shared<TcpNetwork>(serviceBase);
}

void TcpNetwork::SetDisconnected()
{
	if (_connected.exchange(false) == true)
	{
		auto session = _session.lock();
		if (session)
		{
			session->DetachNetwork();
		}
	}
}

void TcpNetwork::SetConnected(EndPoint endPoint)
{
	if (_connected.exchange(true) == false)
	{
		_endPoint = endPoint;

		RegisterRecv(true);
	}
}

void TcpNetwork::Flush()
{
	if (FlushInternal() == false)
	{
		int32 errCode = ::WSAGetLastError();

		HandleError(errCode);
	}
}

bool TcpNetwork::FlushInternal()
{
	if (IsConnected() == false)
	{
		return true;
	}

	WriteData writeData = _sendBuffer.Flush();
	if (writeData.IsEmpty())
	{
		_pending.store(false);
		return true;
	}
	
	return _socket.WriteAsync(std::move(writeData.buffers), SendEvent(shared_from_this(), std::move(writeData.segments)));
}

void TcpNetwork::RegisterRecv(bool init)
{
	if (!IsConnected()) 
	{
		return;
	}

	if (init)
	{
		_recvBuffer.Clear();
	}

	if (!_socket.ReadAsync(_recvBuffer.GetBufferPtr(), _recvBuffer.GetLen(), RecvEvent(shared_from_this())))
	{
		int32 errCode = ::WSAGetLastError();

		HandleError(errCode);
	}
}

void TcpNetwork::DisconnectOnError(const char* reason)
{
	if (!IsConnected())
		return;

	if (!_socket.DisconnectAsync(DisconnectEvent(shared_from_this())))
	{
		LOG_ERROR("disconnect failed on %s : %s", reason, get_last_err_msg());
	}
}

void TcpNetwork::HandleError(int32 errorCode)
{
	switch (errorCode)
	{
	case WSAECONNRESET:
	case WSAECONNABORTED:
		DisconnectOnError("connection reset");
		break;
	default:
		LOG_ERROR("handle error %s", get_last_err_msg_code(errorCode));
		break;
	}
}
