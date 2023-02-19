#pragma once

#include "PacketHandler.h"

namespace Core {
	namespace Network {
		namespace Packet {
			class GamePacketInstaller
			{
			public:
				template<typename T, typename = enable_if_t<is_base_of_v<PacketHandler, T>>>
				static void Install()
				{
					static T handler;

					GPacketHandler = &handler;
				}

				static PacketHandler* GetHandler()
				{
					return GPacketHandler;
				}

			private:
				static PacketHandler* GPacketHandler;
			};
		}
	}
}