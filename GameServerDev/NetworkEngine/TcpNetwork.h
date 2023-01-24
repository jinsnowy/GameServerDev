#pragma once
#include "NetworkStream.h"
#include "TcpActiveSocket.h"

class Handshake;
class TcpNetwork : public std::enable_shared_from_this<TcpNetwork>
{
	friend class TcpListener;
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

public:
	TcpNetwork(ServiceBase& serviceBase);

	~TcpNetwork();

	void AttachSession(SessionPtr session);

	void RequireHandshake(HandshakePtr handshake);

	void SendAsync(const BufferSegment& segment);

	void DisconnectAsync();
	
	void ConnectAsync(const EndPoint& endPoint, const OnConnectFunc& onConnected, const OnConnectFailFunc& onConnectFailed);

	void Start();

	void CloseBy(const wchar_t* reason = L"");

	static shared_ptr<TcpNetwork> Create(ServiceBase& serviceBase);
public:
	SessionPtr GetSession() { return _session.lock(); }

	SOCKET GetSocket() { return _socket.GetSocket(); };

	RecvBuffer& GetRecvBuffer() { return _stream.Recv(); }

	EndPoint GetEndPoint() { return _endPoint; }

	bool IsConnected() { return _connected; }

private:
	void SetDisconnected();

	void SetConnected(EndPoint endPoint);

	void Recv(DWORD bytes);

	void RegisterSend();
	
	void RegisterRecv();

	void SendCloseBy(const wchar_t* reason);

	void HandleError(int32 errorCode, IoType ioType);

private:
	atomic<bool>			_connected;
	atomic<bool>			_pending;
	NetworkStream			_stream;
};