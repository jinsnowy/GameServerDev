#pragma once
#include "Engine/Core/Session/ClientSession.h"

class NetworkManager : public ClientSession
{
public:
	virtual void OnConnected() override;
	virtual void OnDisconnected() override;
};

