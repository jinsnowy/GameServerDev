#pragma once

class TcpConnector : public enable_shared_from_this<TcpConnector>
{
private:
	shared_ptr<Session> _target_session;
	shared_ptr<TcpNetwork> _network;

public:
	TcpConnector(shared_ptr<ClientSession> session, shared_ptr<TcpNetwork> network);

	shared_ptr<Session> Release();

	void Connect(EndPoint endPoint);
};