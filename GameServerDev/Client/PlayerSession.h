#pragma once
#include "ClientSession.h"

class PlayerSession : public ClientSession
{
private:

public:
	PlayerSession();

	virtual void OnConnected() override;
};
