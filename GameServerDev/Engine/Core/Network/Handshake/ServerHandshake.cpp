#include "pch.h"
#include "ServerHandshake.h"

#include "Core/Network/Object/TcpNetwork.h"
#include "Core/Protocol/InternalProtocol.h"
#include "Core/Packet/PacketHeader.h"
#include "Utils/Crypto.h"

using namespace packet;

ServerHandshake::ServerHandshake(NetworkPtr network)
	:
	Handshake(network)
{}

void ServerHandshake::OnProcess(NetworkPtr network)
{
	SetState(Init);
}

void ServerHandshake::OnRecv(PacketHeader* packet)
{
	auto network = _network.lock();
	if (network == nullptr)
	{
		return;
	}

	int protocol = packet->protocol;
	if (protocol == CLIENT_HELLO)
	{
		_uuid = Crypto::GenerateUUID();
		PKT_SERVER_HELLO hello;
		hello.uuid.Set(_uuid);
		network->SendAsync(hello);
		SetState(Hello);

		LOG_INFO(L"Client Hello");
	}
	else if (protocol == AUTH_REQUEST)
	{
		auto auth_request = static_cast<PKT_AUTH_REQUEST*>(packet);
		auto uuid = auth_request->uuid;

		PKT_AUTH_RESPONSE response;

		

		if (uuid.Equal(_uuid) == false) {
			response.success = false;
			response.reason.Set(L"Invalid UUID");
			LOG_INFO(L"Auth Failed");
		}
		else {
			response.success = true;
			network->SetAuthenticated();
			SetState(Auth);
			LOG_INFO(L"Auth Ok");
		}

		network->SendAsync(response);
	}
}