#pragma once

namespace Core {
	namespace Network {
		namespace Packet {
			struct PacketHeader;
		}		
		class TcpNetwork;
		class Handshake
		{
			friend class TcpNetwork;
		protected:
			enum State
			{
				Init,
				Hello,
				Auth,
			};

			State _state;
			weak_ptr<TcpNetwork> _network;

		public:
			Handshake(NetworkPtr network);

			void Process();

			virtual void OnRecv(Packet::PacketHeader* packet);

			virtual void OnAuth();

			template<typename T, typename = std::enable_if_t<std::is_base_of_v<Handshake, T>>>
			static unique_ptr<Handshake> Create(NetworkPtr network) {
				return unique_ptr<Handshake>(new T(network));
			}

			void SetState(State state) { _state = state; }

		protected:
			wstring _uuid;

			virtual void OnProcess(NetworkPtr network) abstract;
		};
	}
}