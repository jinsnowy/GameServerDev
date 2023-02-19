#pragma once

#include "../Session/SessionBase.h"

namespace Core {
	namespace Network {
		namespace Service {
			class ServerService;
			class ServerServiceBuilder : public Builder<ServerServiceBuilder>
			{
			private:
				uint16	 _port;
				int32    _backLog;
				int32	 _acceptCount;
				SessionFactory _sessionFactory;
				NetworkFactory _networkFactory;

			public:
				ServerServiceBuilder();

				shared_ptr<ServerService> Build();

				auto& BackLog(int backLog) {
					_backLog = backLog;
					return self();
				}

				auto& Port(uint16 port) {
					_port = port;
					return self();
				}

				auto& AcceptCount(int32 acceptCount) {
					_acceptCount = acceptCount;
					return self();
				}

				auto& Sessions(SessionFactory sessionFactory) {
					_sessionFactory = sessionFactory;
					return self();
				}

				auto Networks(NetworkFactory networkFactory) {
					_networkFactory = networkFactory;
					return self();
				}
			};
		}
	}
}