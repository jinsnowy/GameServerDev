#include "pch.h"
#include "Handshake.h"
#include "TcpNetwork.h"
#include "Session.h"

Handshake::Handshake(shared_ptr<TcpNetwork> network)
	:
	_network(network)
{}

void Handshake::Process()
{
	auto network = _network.lock();
	if (network)
	{
		onProcess(network);
	}
}

ClientHandshake::ClientHandshake(shared_ptr<TcpNetwork> network)
	:
	Handshake(network)
{
}

void ClientHandshake::onProcess(shared_ptr<TcpNetwork> network)
{
	auto session = network->GetSession();
	if (session == nullptr)
		return;

}

ServerHandshake::ServerHandshake(shared_ptr<TcpNetwork> network)
	:
	Handshake(network)
{}

void ServerHandshake::onProcess(shared_ptr<TcpNetwork> network)
{
}