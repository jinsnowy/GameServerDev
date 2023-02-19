#include "pch.h"
#include "ServerService.h"

#include "Core/Network/Session/SessionManager.h"
#include "Core/Network/Handshake/ServerHandshake.h"
#include "Core/Network/Object/TcpNetwork.h"
#include "Core/Network/Object/TcpListener.h"
#include "Core/Network/Object/TcpListenerBuilder.h"
#include "Core/Database/DatabaseManager.h"

namespace Core {
    namespace Network {
        namespace Service {
            ServerService::ServerService(SessionFactory sessionFactory, NetworkFactory networkFactory)
                :
                ServiceBase(sessionFactory, networkFactory),
                _port(Core::Config::default_port),
                _backLog(10),
                _acceptCount(1)
            {
            }

            void ServerService::Initialize()
            {
                DatabaseManager::GetInstance().Initialize();

                ServiceBase::Initialize();
            }

            void ServerService::Start()
            {
                ServiceBase::Start();

                TcpListenerBuilder builder;
                builder.Port(_port)
                    .BackLog(_backLog)
                    .AcceptCount(_acceptCount)
                    .Factory(_networkFactory);

                ENQUEUE(ServerService, [builder](shared_ptr<ServerService> service) mutable
                    {
                        auto listener = builder.Build(*service);
                        if (!listener->Start())
                        {
                            throw std::exception("TcpListener start failed");
                        }
                    });
            }
        }
    }
}