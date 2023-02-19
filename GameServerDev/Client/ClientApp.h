#pragma once

#include "Engine/Core/Network/Session/ClientSession.h"
#include "ClientState.h"
#include "NetworkManager.h"

class ClientApp : public ISingleton<ClientApp>
{
public:
	ClientApp();


private:
	NetworkManager _networkManager;

public:
	NetworkManager& GetNetworkManger() { return _networkManager; }

public:
	CLIENT_STATE GetState() const;

private:
	CLIENT_STATE _state;
};
