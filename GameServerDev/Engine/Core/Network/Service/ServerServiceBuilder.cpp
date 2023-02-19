#include "pch.h"
#include "ServerServiceBuilder.h"
#include "ServerService.h"

#include "../Session/SessionBase.h"
#include "../Session/ServerSession.h"
#include "../Handshake/ServerHandshake.h"
#include "../Object/TcpNetwork.h"

namespace Core {
    namespace Network {
        namespace Service {
            using namespace Session;

            ServerServiceBuilder::ServerServiceBuilder()
                :
                _backLog(50),
                _port(Core::Config::default_port),
                _acceptCount(10),
                _sessionFactory(CreateSessionFactory<ServerSession>()),
                _networkFactory(TcpNetwork::CreateFactory<ServerHandshake>())
            {
            }

            shared_ptr<ServerService> ServerServiceBuilder::Build()
            {
                auto service = make_shared<ServerService>(_sessionFactory, _networkFactory);
                service->_backLog = _backLog;
                service->_port = _port;

                return service;
            }
        }
    }
}