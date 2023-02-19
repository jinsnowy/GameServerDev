#pragma once

#include "PacketHeader.h"

namespace Core {
	namespace Network {
		class TcpNetwork;
		namespace Session {
			class SessionBase;
		}
		namespace Packet {
			class PacketHandler
			{
			public:
				virtual bool IsValidProtocol(int protocol) abstract;

				virtual void HandleRecv(const std::shared_ptr<TcpNetwork>& network, const PacketHeader& header, char* buffer) {};

				virtual void HandleRecv(const std::shared_ptr<Session::SessionBase>& session, const PacketHeader& header, char* buffer) {};

			protected:
				using SessionPtrCRef = const std::shared_ptr<Session::SessionBase>&;

				template<typename T>
				T* Interpret(char* buffer) { return reinterpret_cast<T*>(buffer); }

				template<typename T>
				T Parse(char* buffer, int len)
				{
					T pkt;
					pkt.ParseFromArray(buffer + sizeof(PacketHeader), len - sizeof(PacketHeader));
					return pkt;
				}

			private:
				static std::vector<PacketHandler*> s_PacketHandler;
			};
		}
	}
}