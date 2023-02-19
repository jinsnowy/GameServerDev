#include "pch.h"

#include "Core/Network/Session/SessionBase.h"
#include "Core/Network/Object/TcpNetwork.h"
#include "Core/Network/Handshake/Handshake.h"
#include "Core/Network/Packet/InternalPacketHandler.h"
#include "Core/Network/Protocol/InternalProtocol.h"

namespace Core {
	namespace Network {
		namespace Packet {
			bool InternalPacketHandler::IsValidProtocol(int32 protocol)
			{
				return protocol >= INTERNAL_PROTOCOL_START && protocol <= INTERNAL_PROTOCOL_END;
			}

			void InternalPacketHandler::HandleRecv(NetworkPtrCRef network, const PacketHeader& header, CHAR* buffer)
			{
				switch (header.protocol)
				{
				case CLOSE_BY:
					OnCloseBy(network, Interpret<PKT_CLOSE_BY>(buffer));
					break;
				case CLIENT_HELLO:
				case SERVER_HELLO:
				case AUTH_REQUEST:
				case AUTH_RESPONSE:
					OnHandshakePacket(network, buffer);
					break;
				}
			}

			void InternalPacketHandler::OnCloseBy(NetworkPtrCRef network, PKT_CLOSE_BY* pkt)
			{
				LOG_INFO(L"network closed by %s", pkt->reason);
			}

			void InternalPacketHandler::OnHandshakePacket(NetworkPtrCRef network, CHAR* buffer)
			{
				ASSERT_CRASH(network->Handshake() != nullptr);
				network->Handshake()->OnRecv((PacketHeader*)buffer);
			}
		}
	}
}