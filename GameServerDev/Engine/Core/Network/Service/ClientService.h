#pragma once
#include "ServiceBase.h"

namespace Core {
	namespace Network {
		class TcpConnector;
		namespace Buffer {
			struct BufferSegment;
		}
		namespace Service {
			class ClientService : public ServiceBase
			{
				friend class ClientServiceBuilder;
			private:
				int _clientNum;
				EndPoint _endPoint;
				vector<shared_ptr<TcpConnector>> _connectors;

			public:
				ClientService(SessionFactory sessionFactory, NetworkFactory networkFactory);

				virtual void Initialize();

				virtual void Start() override;

				void Broadcast(Buffer::BufferSegment buffer);

				void ForEach(function<void(SessionPtr)> func);

			private:
				void StartConnection();
			};
		}
	}
}