#pragma once

class Session : public std::enable_shared_from_this<Session>
{
	friend class TcpNetwork;
	friend class TcpListener;
public:
	Session();

	virtual ~Session();

public:
	void SendAsync(const BufferSegment& segment);

	template<typename T>
	shared_ptr<T> GetShared() { return static_pointer_cast<T>(shared_from_this()); }

	bool IsConnected();

	void Disconnect();

	void DisconnectAsync();

protected:
	shared_ptr<TcpNetwork> _network;

	virtual void OnConnected();
	virtual void OnDisconnected();

public:
	EndPoint	 GetEndPoint();
	string		 GetEndPointDesc() { return GetEndPoint().ToString(); }
	NetworkPtr	 GetNetwork() { return _network; }

	SessionID	 GetSessionId() { return _sessionId; }
	void		 SetSessionId(SessionID sessionId) { _sessionId = sessionId; }

private:
	SessionID _sessionId;

	void AttachNetwork(shared_ptr<TcpNetwork> network);
	void DetachNetwork();
};