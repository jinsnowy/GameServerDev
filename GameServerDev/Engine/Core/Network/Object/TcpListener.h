#pragma once

#include "../../System/Actor/Actor.h"
#include "TcpListenerNetwork.h"

namespace Core {
	namespace Network {
		namespace Service {
			class ServiceBase;
		}

		class TcpListener : public System::Actor::Actor
		{
			friend struct AcceptEvent;
			friend class TcpListenerBuilder;
		private:
			Service::ServiceBase& _serviceBase;
			atomic<bool>   _finished;
			uint16		   _bindPort;
			int32		   _backLog;
			int32		   _acceptCount;
			NetworkFactory _networkFactory;

		public:
			TcpListener(Service::ServiceBase& serviceBase);
			~TcpListener();

			bool Start();
			void Stop();
		private:
			bool ProcessAccept(const NetworkPtr& network);
			void RegisterAccept();

			TcpListenerNetwork _listenerNetwork;
		};
	}
}