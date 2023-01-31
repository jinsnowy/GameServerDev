#pragma once
#include "ServerSession.h"

class UserSession : public ServerSession
{
public:
	UserSession();

	virtual void OnConnected();
};
