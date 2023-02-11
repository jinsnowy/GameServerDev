#pragma once

#include "ClientServiceMock.h"
#include "NetworkMock.h"

class ClientMock
{
protected:
	unique_ptr<ClientServiceMock> _serviceMock;
	shared_ptr<NetworkMock> _networkMock;

	shared_ptr<Session> _serverSession;
	weak_ptr<NetworkMock> _serverSideNetworkMock;

public:
	ClientMock();

	void Initialize();

	auto GetNetworkMock() { return _networkMock; }

	void SetServer(shared_ptr<NetworkMock> network)
	{
		_serverSideNetworkMock = network;
	}

	template<typename T>
	void Send(const T& packet)
	{
		if (auto network = _serverSideNetworkMock.lock(); network != nullptr) {
			network->RecvMock(packet);
		}
	}

	template<typename T>
	void Recv(const T& packet)
	{
		_networkMock->RecvMock(packet);
	}
};

