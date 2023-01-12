#pragma once

#include "TcpActiveSocket.h"
#include "RecvBuffer.h"
#include "SendBuffer.h"

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
	unique_ptr<Handshake>  _handshake;

public:
	TcpNetwork(ServiceBase& ServiceBase);

	~TcpNetwork();

	void AttachSession(SessionPtr session);

	void ProcessHandshake();

	void RequireHandshake(Handshake* handshake);

	void SendAsync(const BufferSegment& segment);

	void DisconnectAsync();
	
	void ConnectAsync(const EndPoint& endPoint);

	void Start();
public:
	SessionPtr GetSession() { return _session.lock(); }

	SOCKET GetSocket() { return _socket.GetSocket(); };

	RecvBuffer& GetRecvBuffer() { return _recvBuffer; }

	EndPoint GetEndPoint() { return _endPoint; }

	bool IsConnected() { return _connected; }

private:
	void SetDisconnected();

	void SetConnected(EndPoint endPoint);

	void Recv(DWORD bytes);

	void Flush();
	
	bool FlushInternal();
	
	void RegisterRecv(bool init = false);

	void DisconnectOnError(const char* reason = "");

	void HandleError(int32 errorCode);

private:
	atomic<bool>			_connected;
	atomic<bool>			_pending;
	RecvBuffer				_recvBuffer;
	SendBuffer				_sendBuffer;
};