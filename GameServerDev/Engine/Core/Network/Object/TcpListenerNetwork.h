#pragma once

#include "../Socket/TcpListenerSocket.h"

namespace Core {
	namespace Network {
		namespace Service {
			class ServiceBase;
		}

		class TcpListenerNetwork
		{
		private:
			Socket::TcpListenerSocket  _listenerSocket;

		public:
			TcpListenerNetwork(Service::ServiceBase& serviceBase);

			~TcpListenerNetwork();

			bool Initialize();

			bool Bind(uint16 port);

			bool Listen(int32 backLog);

			EndPoint GetBindAddress();

			bool AcceptAsync(ListenerPtr listener, NetworkPtr network, LPVOID bufferPtr);

			bool UpdateAcceptSocket(SOCKET socket);

			void Finish();

			bool IsFinished();
		};
	}
}