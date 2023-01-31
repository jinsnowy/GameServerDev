#pragma once
#include "Session.h"

class ServerSession : public Session
{
public:
	ServerSession();

protected:
	virtual void OnConnected() override;

	virtual void OnDisconnected() override;
};
