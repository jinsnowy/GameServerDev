#include "pch.h"
#include "ClientServiceBuilder.h"
#include "ClientService.h"

#include "../Session/ClientSession.h"
#include "../Handshake/ClientHandshake.h"
#include "../Object/TcpNetwork.h"

namespace Core {
	namespace Network {
		namespace Service {
			using namespace Session;

			ClientServiceBuilder::ClientServiceBuilder()
				:
				_endPoint("127.0.0.1", Core::Config::default_port),
				_clientNum(1),
				_sessionFactory(CreateSessionFactory<ClientSession>()),
				_networkFactory(TcpNetwork::CreateFactory<ClientHandshake>())
			{
			}

			shared_ptr<ClientService> ClientServiceBuilder::Build()
			{
				auto service = make_shared<ClientService>(_sessionFactory, _networkFactory);
				service->_endPoint = _endPoint;
				service->_clientNum = _clientNum;

				return service;
			}
		}
	}
}