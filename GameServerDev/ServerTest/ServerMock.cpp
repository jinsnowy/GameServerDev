#include "pch.h"
#include "ServerMock.h"
#include "ServerSessionMock.h"

ServerMock::ServerMock()
{
}

void ServerMock::Initialize()
{
	const auto network_factory = TcpNetwork::CreateFactory<NetworkMock>();
	const auto session_factory = Session::CreateSessionFactory<ServerSessionMock>();

	_serviceMock = make_unique<ServerServiceMock>(session_factory, network_factory);
	_serviceMock->Initialize();

	_networkMock = network_factory(*_serviceMock);
	_networkMock->SetConnectedMock();

	_serverSession = session_factory();
	_networkMock->AttachSession(_serverSession);
}
