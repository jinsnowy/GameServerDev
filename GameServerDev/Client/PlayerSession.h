#pragma once
#include "Engine/ClientSession.h"

class PlayerSession : public ClientSession
{
private:

public:
	PlayerSession();

	virtual void OnConnected() override;
};
