#include "pch.h"
#include "ClientHandshake.h"
#include "Core/Network/Object/TcpNetwork.h"
#include "Core/Protocol/InternalProtocol.h"
#include "Core/Packet/PacketHeader.h"

using namespace packet;

ClientHandshake::ClientHandshake(NetworkPtr network)
	:
	Handshake(network)
{
}

void ClientHandshake::OnProcess(NetworkPtr network)
{
	SetState(Init);

	PKT_CLIENT_HELLO hello;
	network->SendAsync(hello);
}

void ClientHandshake::OnRecv(packet::PacketHeader* packet)
{
	auto network = _network.lock();
	if (network == nullptr)
	{
		return;
	}

	int protocol = packet->protocol;
	if (protocol == SERVER_HELLO)
	{
		auto hello = static_cast<PKT_SERVER_HELLO*>(packet);
		auto uuid = hello->uuid;

		_uuid = uuid.ToString();

		auto auth_request = PKT_AUTH_REQUEST();
		auth_request.uuid.CopyFrom(uuid);

		network->SendAsync(auth_request);
		SetState(Hello);
	}
	else if (protocol == AUTH_RESPONSE)
	{
		auto auth_response = static_cast<PKT_AUTH_RESPONSE*>(packet);
		bool success = auth_response->success;

		if (success) {
			network->SetAuthenticated();
			SetState(Auth);
		}
		else {
			LOG_ERROR(L"Auth Failed");
			network->CloseBy(L"Auth Failed");
		}
	}
}