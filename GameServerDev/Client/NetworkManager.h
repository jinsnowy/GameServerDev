#pragma once

#include "Engine/Core/Network/Session/ClientSession.h"

class NetworkManager : public Core::Network::Session::ClientSession
{
public:
	virtual void OnConnected() override;
	virtual void OnDisconnected() override;
};

