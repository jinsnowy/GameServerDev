#include "pch.h"
#include "TcpNetwork.h"
#include "Session.h"
#include "NetworkEvent.h"
#include "InternalPacketHandler.h"
#include "GamePacketInstaller.h"
#include "Handshake.h"

TcpNetwork::TcpNetwork(ServiceBase& serviceBase)
	:
	_socket(serviceBase),
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
		CloseBy(L"recv buffer overflows");
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

		if (session == nullptr) 
		{
			CloseBy(L"null session");
			return;
		}

		if (GamePacketHandler->IsValidProtocol(header.protocol) == false)
		{
			CloseBy(L"unknown protocol");
			return;	
		}

		GamePacketHandler->HandleRecv(session, header, bufferToRead);
	}

	_recvBuffer.Rotate();
}

void TcpNetwork::SendAsync(const BufferSegment& segment)
{
	if (_connected == false) {
		return;
	}

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
		LOG_ERROR(L"disconnect failed %s", get_last_err_msg());
	}
}

void TcpNetwork::ConnectAsync(const EndPoint& endPoint, const OnConnectFunc& onConnected, const OnConnectFailFunc& onConnectFailed)
{
	if (NetUtils::SetReuseAddress(_socket.GetSocket(), true) == false)
	{
		LOG_ERROR(L"connect failed to %s, %s", endPoint.ToString().c_str(), get_last_err_msg());
		return;
	}

	if (NetUtils::BindAnyAddress(_socket.GetSocket(), 0) == false)
	{
		LOG_ERROR(L"connect failed to %s, %s", endPoint.ToString().c_str(), get_last_err_msg());
		return;
	}

	if (!_socket.ConnectAsync(endPoint, ConnectEvent(shared_from_this(), endPoint, onConnected, onConnectFailed)))
	{
		LOG_ERROR(L"connect failed to %s, %s", endPoint.ToString().c_str(), get_last_err_msg());
	}
}

void TcpNetwork::Start()
{
	_recvBuffer.Clear();
	_sendBuffer.Clear();
	_pending = false;

	RegisterRecv();
}

void TcpNetwork::CloseBy(const wchar_t* reason)
{
	if (_socket.IsOk())
	{
		SendCloseBy(reason);

		DisconnectAsync();

		return;
	}

	if (_connected)
	{
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

		HandleError(errCode, IO_WRITE);
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

		HandleError(errCode, IO_READ);
	}
}

void TcpNetwork::SendCloseBy(const wchar_t* reason)
{
	if (lstrlenW(reason) > 0)
	{
		SendAsync(Serializer::SerializeStruct(PKT_CLOSE_BY(reason)));
	}
}

void TcpNetwork::HandleError(int32 errorCode, IoType ioType)
{
	switch (errorCode)
	{
	case WSAECONNRESET:
	case WSAECONNABORTED:
		CloseBy(L"connection reset");
		break;
	default:
	{
		wstring reason = get_last_err_msg_code(errorCode);
		LOG_ERROR(L"handle error reason : %s", reason.c_str());
		CloseBy(reason.c_str());
		break;
	}
	}
}
