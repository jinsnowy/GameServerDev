#include "pch.h"
#include "Handshake.h"
#include "Core/Network/Object/TcpNetwork.h"
#include "Core/Packet/PacketHeader.h"

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

void Handshake::OnRecv(packet::PacketHeader* packet)
{
}

void Handshake::OnAuth()
{
	SetState(Auth);
}