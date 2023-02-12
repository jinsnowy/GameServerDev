#include "pch.h"
#include "ClientService.h"
#include "Core/Session/ClientSession.h"
#include "Core/Session/SessionManager.h"
#include "Core/Network/Handshake/ClientHandshake.h"
#include "Core/Network/Object/TcpNetwork.h"
#include "Core/Network/Object/TcpConnector.h"

ClientService::ClientService(SessionFactory sessionFactory, NetworkFactory networkFactory)
	:
	ServiceBase(sessionFactory, networkFactory),
	_clientNum(1)
{
}

void ClientService::Initialize()
{
	ServiceBase::Initialize();
}

void ClientService::Start()
{
	ServiceBase::Start();

	_connectors.clear();

	std::this_thread::sleep_for(2s);

	wstring target_address = _endPoint.ToString();

	ENQUEUE_MEM(&ClientService::StartConnection);
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
			client->Send(buffer);
		}
	}

	LOG_INFO(L"client %d connected", count);
}

void ClientService::ForEach(function<void(SessionPtr)> func)
{
	ENQUEUE(ClientService, [func](shared_ptr<ClientService> service)
	{
		auto clients = service->GetSessionManager().GetSessions();

		for (auto& client : clients)
		{
			func(client);
		}
	});
}

void ClientService::StartConnection()
{
	for (int i = 0; i < _clientNum; ++i)
	{
		auto network = _networkFactory(*this);
		auto connector = make_shared<TcpConnector>(network);

		connector->Connect(_endPoint);

		_connectors.push_back(connector);
	}
}
