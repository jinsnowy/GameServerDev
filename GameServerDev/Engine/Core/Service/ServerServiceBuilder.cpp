#include "pch.h"
#include "ServerServiceBuilder.h"
#include "ServerService.h"

#include "../Session/Session.h"
#include "../Session/ServerSession.h"
#include "../Network/Handshake/ServerHandshake.h"
#include "../Network/Object/TcpNetwork.h"

ServerServiceBuilder::ServerServiceBuilder()
    :
    _backLog(50),
    _port(Core::Config::default_port),
    _acceptCount(10),
    _sessionFactory([]() { return std::shared_ptr<Session>(new ServerSession()); }),
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