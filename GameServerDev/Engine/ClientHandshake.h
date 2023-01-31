#pragma once
#include "Handshake.h"

class ClientHandshake : public Handshake
{
public:
	ClientHandshake(NetworkPtr network);

protected:
	virtual void OnProcess(NetworkPtr network) override;

	virtual void OnRecv(packet::PacketHeader* packet) override;
};