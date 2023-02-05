#pragma once

struct BufferSegment;
struct ThreadContext;
class Session : public std::enable_shared_from_this<Session>
{
	friend class TcpNetwork;
	friend class TcpListener;
public:
	Session();

	virtual ~Session();

public:
	ThreadContext* GetContext();

	template<typename T>
	shared_ptr<T> GetShared() { return static_pointer_cast<T>(shared_from_this()); }

	template <typename T>
	requires std::is_copy_constructible_v<T>&& std::is_copy_assignable_v<T>
	void Send(const T& message) {
		if constexpr (std::is_same_v<BufferSegment, T>) {
			SendInternal(message);
		}
		else {
			SendInternal(Serializer::SerializeProtoBuf(message));
		}
	}

	bool IsConnected();

	void Disconnect();

	void DisconnectAsync();

	template<typename T, typename = enable_if_t<is_base_of_v<Session, T>>>
	static SessionFactory CreateSessionFactory() {
		return []() { return SessionPtr(new T()); };
	}

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

	void SendInternal(const BufferSegment& segment);
};