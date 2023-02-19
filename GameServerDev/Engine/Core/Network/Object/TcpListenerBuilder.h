#pragma once

namespace Core {
	namespace Network {
		namespace Service {
			class ServiceBase;
		}
		class TcpListenerBuilder : public Builder<TcpListenerBuilder>
		{
		private:
			uint16		   _bindPort;
			int32		   _backLog;
			int32		   _acceptCount;
			NetworkFactory _networkFactory;

		public:
			TcpListenerBuilder();

			TcpListenerBuilder& Port(uint16 port);
			TcpListenerBuilder& BackLog(int32 backLog);
			TcpListenerBuilder& AcceptCount(int32 acceptCount);
			TcpListenerBuilder& Factory(NetworkFactory networkFactory);

			shared_ptr<class TcpListener> Build(Service::ServiceBase& serviceBase);
		};

	}
}