#include "pch.h"
#include "ClientHandshake.h"
#include "TcpNetwork.h"
#include "Session.h"
#include "InternalProtocol.h"

ClientHandshake::ClientHandshake(NetworkPtr network)
	:
	Handshake(network)
{
}

void ClientHandshake::OnProcess(NetworkPtr network)
{
	SetState(Init);

	PKT_CLIENT_HELLO hello;
	network->SendAsync(Serializer::SerializeStruct(hello));
}

void ClientHandshake::OnRecv(PacketHeader* packet)
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

		network->SendAsync(Serializer::SerializeStruct(auth_request));
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