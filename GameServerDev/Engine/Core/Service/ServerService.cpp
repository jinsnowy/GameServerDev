#include "pch.h"
#include "ServerService.h"

#include "Core/Session/SessionManager.h"
#include "Core/Network/Handshake/ServerHandshake.h"
#include "Core/Network/Object/TcpNetwork.h"
#include "Core/Network/Object/TcpListener.h"
#include "Core/Network/Object/TcpListenerBuilder.h"

ServerService::ServerService(SessionFactory sessionFactory, NetworkFactory networkFactory)
	:
	ServiceBase(sessionFactory, networkFactory),
    _port(Config::default_port),
    _backLog(10),
	_acceptCount(1)
{
}

void ServerService::Initialize()
{
	ServiceBase::Initialize();

	DatabaseManager::Config config;
	config.connCount = Config::thread_count;
	config.connstr = Config::dbsn;

	if (_dbManager.Initialize(config) == false) {
		return;
	}

	try
	{
		for (size_t idx = 0; idx < _threadContexts.size(); ++idx)
		{
			_threadContexts[idx]->dbConn = _dbManager.GetConnection();

			for (auto& [tag, factory] : _repository_factories)
			{
				_threadContexts[idx]->repositories[tag] = factory();
				_threadContexts[idx]->repositories[tag]->Initialize(_threadContexts[idx]->dbConn);
			}
		}
	}
	catch (std::exception e) {
		LOG_ERROR(L"init failed : %s", e.what());
		throw e;
	}
}

void ServerService::Start()
{
    ServiceBase::Start();

    TcpListenerBuilder builder;
    builder.Port(_port)
        .BackLog(_backLog)
        .AcceptCount(_acceptCount)
        .Factory(_networkFactory);

    auto listener = builder.Build(*this);
    if (!listener->Start())
    {
        throw std::exception("TcpListener start failed");
    }
}