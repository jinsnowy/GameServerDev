#pragma once
#include "ClientSession.h"

class PlayerSession : public ClientSession
{
private:
	UserProtocol::Player _player;

public:
	PlayerSession(ServiceBase& _serviceBase);

	virtual void OnConnected() override;

	void SetPlayer(UserProtocol::Player player) { _player = player; }
};
