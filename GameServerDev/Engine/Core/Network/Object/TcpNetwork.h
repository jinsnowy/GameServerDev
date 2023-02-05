#pragma once

#include "../../Buffer/NetworkStream.h"
#include "../Socket/TcpActiveSocket.h"

namespace packet {
	class PacketHandler;
}

class Handshake;
class ServiceBase;
class TcpNetwork : public std::enable_shared_from_this<TcpNetwork>
{
	friend class TcpListener;
	friend class Handshake;
	friend struct AcceptEvent;
	friend struct ConnectEvent;
	friend struct DisconnectEvent;
	friend struct RecvEvent;
	friend struct SendEvent;
private:
	TcpActiveSocket _socket;
	SessionWeakPtr  _session;
	EndPoint		_endPoint;
	HandshakePtr    _handshake;
	time_t			_connected_time;

public:
	TcpNetwork(ServiceBase& serviceBase);

	~TcpNetwork();

	void AttachSession(SessionPtr session);

	template <typename T, typename = std::enable_if_t<std::is_copy_constructible_v<T>&& std::is_copy_assignable_v<T> && (!std::is_polymorphic_v<T>)>>
	void SendAsync(const T& message) {
		if constexpr (std::is_same_v<T, BufferSegment>) {
			SendAsyncInternal(message);
		}
		else {
			SendAsyncInternal(Serializer::SerializeStruct(message));
		}
	}

	void DisconnectAsync();
	
	void ConnectAsync(const EndPoint& endPoint, const OnConnectFunc& onConnected, const OnConnectFailFunc& onConnectFailed);

	void Start();

	void CloseBy(const wchar_t* reason = L"");

	template <typename HandshakeType>
	static NetworkFactory CreateFactory()
	{
		return [](ServiceBase& serviceBase)
		{
			auto network = std::make_shared<TcpNetwork>(serviceBase);
			auto handshake = Handshake::Create<HandshakeType>(network);
			network->RequireHandshake(MOVE(handshake));

			return network;
		};
	}

public:
	ServiceBase& AssociateService();

	SessionPtr GetSession() { return _session.lock(); }

	SOCKET GetSocket() { return _socket.GetSocket(); };

	RecvBuffer& GetRecvBuffer() { return _stream.Recv(); }

	EndPoint GetEndPoint() { return _endPoint; }

	bool IsConnected() { return _connected; }

public:
	void RequireHandshake(HandshakePtr handshake);

	HandshakePtr& Handshake() { return _handshake; }

	void SetAuthenticated();

protected:
	void SendAsyncInternal(const BufferSegment& segment);

	void SetDisconnected();

	void SetConnected(EndPoint endPoint);

	void Recv(DWORD bytes);

	void Recv(DWORD bytes, packet::PacketHandler* handler);

	void RegisterSend();
	
	void RegisterRecv();

	void SendCloseBy(const wchar_t* reason);

	void HandleError(int32 errorCode, IoType ioType);

private:
	atomic<bool>			_connected;
	atomic<bool>			_pending;
	NetworkStream			_stream;
};