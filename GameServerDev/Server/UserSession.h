#pragma once

class UserSession : public Core::Network::Session::ServerSession
{
public:
	UserSession();

	virtual void OnConnected();
};
