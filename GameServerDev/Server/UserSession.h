#pragma once
#include "Engine/ServerSession.h"

class UserSession : public ServerSession
{
public:
	UserSession();

	virtual void OnConnected();
};
