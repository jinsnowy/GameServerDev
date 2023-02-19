#pragma once
#include "Handshake.h"

namespace Core {
	namespace Network {
		class ClientHandshake : public Handshake
		{
		public:
			ClientHandshake(NetworkPtr network);

		protected:
			virtual void OnProcess(NetworkPtr network) override;

			virtual void OnRecv(Packet::PacketHeader* packet) override;
		};
	}
}