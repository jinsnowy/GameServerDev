#include "pch.h"
#include "ServerService.h"
#include "TcpListener.h"
#include "SessionManager.h"
#include "Handshake.h"
#include "TcpNetwork.h"
#include "TcpListenerBuilder.h"
#include "Alarm.h"

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

    TcpListenerBuilder builder;
    builder.Port(_port)
        .BackLog(_backLog)
        .AcceptCount(10)
        ._NetworkFactory([](ServiceBase& serviceBase) { return make_shared<TcpNetwork>(serviceBase); })
        ._SessionFactory(_sessionFactory);

    Alarm::Register("health check", 1000, true, []()
    {
        auto sessions = SessionManager::GetInstance()->GetSessions();

        LOG_INFO(L"session count %zd", sessions.size());
    });


    auto listener = builder.Build(*this);
    if (!listener->Start())
    {
        throw std::exception("TcpListener start failed");
    }
}