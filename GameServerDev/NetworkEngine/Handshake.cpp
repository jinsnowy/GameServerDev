#include "pch.h"
#include "Handshake.h"
#include "TcpNetwork.h"
#include "Session.h"
#include "InternalProtocol.h"

Handshake::Handshake(NetworkPtr network)
	:
	_network(network),
	_state(Init)
{}

void Handshake::Process()
{
	auto network = _network.lock();
	if (network)
	{
		OnProcess(network);
	}
}

void Handshake::OnRecv(PacketHeader* packet)
{
}

void Handshake::OnAuth()
{
	SetState(Auth);
}