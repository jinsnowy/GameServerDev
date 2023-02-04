#pragma once
#include "Engine/Core/Session/ServerSession.h"

class UserSession : public ServerSession
{
public:
	UserSession();

	virtual void OnConnected();
};
