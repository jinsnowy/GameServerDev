#pragma once
#include "Handshake.h"

namespace Core {
	namespace Network {
		class ServerHandshake : public Handshake
		{
		public:
			ServerHandshake(NetworkPtr network);

		protected:
			virtual void OnProcess(NetworkPtr network) override;

			virtual void OnRecv(Packet::PacketHeader* packet) override;
		};
	}
}