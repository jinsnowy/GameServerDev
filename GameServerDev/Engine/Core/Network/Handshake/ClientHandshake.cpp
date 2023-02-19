#include "pch.h"
#include "ClientHandshake.h"
#include "Core/Network/Object/TcpNetwork.h"
#include "Core/Network/Protocol/InternalProtocol.h"
#include "Core/Network/Packet/PacketHeader.h"

namespace Core {
	namespace Network {

		using namespace Protocol;
		using namespace Packet;

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

				network->SendAsync(auth_request);
				SetState(Hello);

				LOG_INFO(L"Server Hello");
			}
			else if (protocol == AUTH_RESPONSE)
			{
				auto auth_response = static_cast<PKT_AUTH_RESPONSE*>(packet);
				bool success = auth_response->success;

				if (success) {
					network->SetAuthenticated();
					SetState(Auth);
					LOG_INFO(L"Auth Ok");
				}
				else {
					LOG_ERROR(L"Auth Failed");
					network->CloseBy(L"Auth Failed");
				}
			}
		}
	}
}