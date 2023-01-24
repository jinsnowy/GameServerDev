#include "pch.h"
#include "ClientService.h"
#include "ClientSession.h"
#include "ClientHandshake.h"
#include "TcpNetwork.h"
#include "SessionManager.h"

ClientService::ClientService(SessionManager& sessionManager, const ClientServiceParam& param)
	:
	ServiceBase(sessionManager, param.workerNum),
	_clientNum(param.clientNum),
	_endPoint(param.address, param.port)
{
}

void ClientService::Start()
{
	ServiceBase::Start();

	std::this_thread::sleep_for(2s);

	const auto connectorFactory = [this]()
	{
		auto network = TcpNetwork::Create(*this);
		auto handshake = Handshake::Create<ClientHandshake>(network);
		network->RequireHandshake(MOVE(handshake));

		return network;
	};

	for (int i = 0; i < _clientNum; ++i)
	{
		auto clientSession = _sessionManager.NewSession()->GetShared<ClientSession>();

		clientSession->_connectorFactory = connectorFactory;

		clientSession->ConnectAsync(_endPoint);
	}
}

void ClientService::Broadcast(BufferSegment buffer)
{
	int count = 0;
	auto clients = _sessionManager.GetSessions();

	for (auto& client : clients)
	{
		if (client->IsConnected())
		{
			++count;
			client->SendAsync(buffer);
		}
	}

	LOG_INFO(L"client %d connected", count);
}

void ClientService::ForEach(function<void(SessionPtr)> func)
{
	auto clients = _sessionManager.GetSessions();

	for (auto& client : clients)
	{
		func(client);
	}
}
