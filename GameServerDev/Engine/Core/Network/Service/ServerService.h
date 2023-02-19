#pragma once
#include "ServiceBase.h"
#include "../Session/ServerSession.h"

namespace Core {
	namespace Network {
		namespace Service {
			class ServerService : public ServiceBase
			{
				friend class ServerServiceBuilder;
			private:
				uint16 _port;
				int32 _backLog;
				int32 _acceptCount;

			public:
				ServerService(SessionFactory sessionFactory, NetworkFactory networkFactory);

				virtual void Initialize();

				virtual void Start() override;
			};
		}
	}
}