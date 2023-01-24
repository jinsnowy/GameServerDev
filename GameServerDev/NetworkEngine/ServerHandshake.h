#pragma once
#include "Handshake.h"

class ServerHandshake : public Handshake
{
public:
	ServerHandshake(NetworkPtr network);

protected:
	virtual void OnProcess(NetworkPtr network) override;

	virtual void OnRecv(PacketHeader* packet) override;
};