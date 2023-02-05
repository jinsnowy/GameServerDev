#include "pch.h"
#include "ClientServiceBuilder.h"
#include "ClientService.h"

#include "../Session/ClientSession.h"
#include "../Network/Handshake/ClientHandshake.h"
#include "../Network/Object/TcpNetwork.h"

ClientServiceBuilder::ClientServiceBuilder()
	:
	_endPoint("127.0.0.1", Config::default_port),
	_clientNum(1),
	_sessionFactory(Session::CreateSessionFactory<ClientSession>()),
	_networkFactory(TcpNetwork::CreateFactory<ClientHandshake>())
{
}

unique_ptr<ClientService> ClientServiceBuilder::Build()
{
	auto service = make_unique<ClientService>(_sessionFactory, _networkFactory);
	service->_endPoint = _endPoint;
	service->_clientNum = _clientNum;

	return service;
}
