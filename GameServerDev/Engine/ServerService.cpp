#include "pch.h"
#include "ServerService.h"
#include "ServerHandshake.h"

#include "TcpNetwork.h"
#include "TcpListener.h"
#include "TcpListenerBuilder.h"
#include "SessionManager.h"

#include "Alarm.h"

ServerService::ServerService(SessionManager& sessionManager, const ServerServiceParam& param)
	:
	ServiceBase(sessionManager, std::thread::hardware_concurrency()),
	_port(param.port),
	_backLog(param.backLog)
{
}

void ServerService::Start()
{
    ServiceBase::Start();

    auto networkFactory = [](ServiceBase& serviceBase) 
    {
        auto network = TcpNetwork::Create(serviceBase);
        auto handshake = Handshake::Create<ServerHandshake>(network);
        network->RequireHandshake(MOVE(handshake));

        return network;
    };

    TcpListenerBuilder builder;
    builder.Port(_port)
        .BackLog(_backLog)
        .AcceptCount(10)
        ._NetworkFactory(networkFactory);

    //Alarm::Register("health check", 1000, true, []()
    //{
    //    auto sessions = SessionManager::GetInstance()->GetSessions();

    //    LOG_INFO(L"session count %zd", sessions.size());
    //});

    auto listener = builder.Build(*this);
    if (!listener->Start())
    {
        throw std::exception("TcpListener start failed");
    }
}