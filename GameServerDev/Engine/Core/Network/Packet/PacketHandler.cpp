#include "pch.h"
#include "PacketHandler.h"

namespace Core {
	namespace Network {
		namespace Packet {
			vector<PacketHandler*> PacketHandler::s_PacketHandler = {};
		}
	}
}