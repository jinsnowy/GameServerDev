#pragma once

#include "Engine/Core/Session/ServerSession.h"
#include "Contents/ServerPacketHandler.h"

#include "ServerServiceMock.h"
#include "NetworkMock.h"

class ServerMock
{
protected:
	unique_ptr<ServerServiceMock> _serviceMock;
	shared_ptr<NetworkMock> _networkMock;
	shared_ptr<Session> _serverSession;

	weak_ptr<NetworkMock> _clientSideNetworkMock;
	packet::ServerPacketHandler _packetHandler;

public:
	ServerMock();

	void Initialize();

	auto GetNetworkMock() { return _networkMock; }

	void SetClient(shared_ptr<NetworkMock> network) 
	{
		_clientSideNetworkMock = network;
	}

	template<typename T>
	void Send(const T& packet)
	{
		if (auto network = _clientSideNetworkMock.lock(); network != nullptr) 
		{
			network->RecvMock(packet);
		}
	}

	template<typename T>
	void Recv(const T& packet) 
	{
		_networkMock->RecvMock(packet, &_packetHandler);
	}
};

