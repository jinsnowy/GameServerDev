#include "pch.h"
#include "Handshake.h"
#include "Core/Network/Object/TcpNetwork.h"
#include "Core/Network/Packet/PacketHeader.h"

namespace Core {
	namespace Network {
		using namespace Protocol;
		using namespace Packet;

		Handshake::Handshake(NetworkPtr network)
			:
			_network(network),
			_state(Init)
		{}

		void Handshake::Process()
		{
			auto network = _network.lock();
			if (network)
			{
				OnProcess(network);
			}
		}

		void Handshake::OnRecv(PacketHeader* packet)
		{
		}

		void Handshake::OnAuth()
		{
			SetState(Auth);
		}
		
	}
}