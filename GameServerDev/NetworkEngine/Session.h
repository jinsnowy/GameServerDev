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

	virtual void AttachNetwork(shared_ptr<TcpNetwork> network) sealed;
	virtual void DetachNetwork() sealed;

public:
	EndPoint	 GetEndPoint();
	wstring		 GetEndPointDesc() { return GetEndPoint().ToString(); }
	NetworkPtr	 GetNetwork() { return _network; }

	SessionID	 GetSessionId() { return _sessionId; }
	void		 SetSessionId(SessionID sessionId) { _sessionId = sessionId; }

private:
	SessionID _sessionId;
};