#pragma once

#include "PacketHandler.h"
#include "Core/Network/Protocol/InternalProtocol.h"

namespace Core {
	namespace Network {
		namespace Packet {
			using namespace Protocol;

			class InternalPacketHandler : public PacketHandler
			{
			public:
				bool IsValidProtocol(int32 protocol) override;

				void HandleRecv(NetworkPtrCRef network, const PacketHeader& header, CHAR* buffer) override;

			private:
				template<typename T>
				T* interpret(CHAR* buffer) { return reinterpret_cast<T*>(buffer); }

				static void OnCloseBy(NetworkPtrCRef network, PKT_CLOSE_BY* pkt);
				static void OnHandshakePacket(NetworkPtrCRef session, CHAR* buffer);
			};
		}
	}
}
