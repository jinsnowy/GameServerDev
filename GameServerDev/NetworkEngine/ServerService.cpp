#include "pch.h"
#include "ServerService.h"
#include "TcpListener.h"
#include "SessionManager.h"
#include "Handshake.h"
#include "TcpNetwork.h"

ServerService::ServerService(const ServerServiceParam& param)
	:
	ServiceBase(std::thread::hardware_concurrency()),
	_port(param.port),
	_backLog(param.backLog),
    _sessionFactory(param.sessionFactory)
{
}

void ServerService::Start()
{
    ServiceBase::Start();

    ListenerConfig config;
    config.bindPort = 12321;
    config.backLog = 10;
    config.acceptCount = 1;
    config.onAccept = [this](const shared_ptr<TcpNetwork>& network)
    {
        auto session = _sessionFactory();
        network->AttachSession(session);

        SessionManager::GetInstance()->AddSession(session);

        return true;
    };

    config.networkFactory = [](ServiceBase& ServiceBase)
    {
        return make_shared<TcpNetwork>(ServiceBase);
    };

    auto listener = make_shared<TcpListener>(*this, config);
    if (!listener->Start())
    {
        throw std::exception("TcpListener start failed");
    }
}