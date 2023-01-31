#pragma once
#include "PacketHandler.h"
#include "InternalProtocol.h"

namespace packet
{
	class InternalPacketHandler : public PacketHandler
	{
	public:
		virtual bool IsValidProtocol(int32 protocol) override
		{
			return protocol >= INTERNAL_PROTOCOL_START && protocol <= INTERNAL_PROTOCOL_END;
		}

		virtual void HandleRecv(NetworkPtrCRef network, const PacketHeader& header, CHAR* buffer) override
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

	private:
		template<typename T>
		T* interpret(CHAR* buffer) { return reinterpret_cast<T*>(buffer); }

		static void OnCloseBy(NetworkPtrCRef network, PKT_CLOSE_BY* pkt);
		static void OnHandshakePacket(NetworkPtrCRef session, CHAR* buffer);
	};
}