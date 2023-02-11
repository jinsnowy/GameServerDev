#include "pch.h"
#include "ClientMock.h"
#include "ClientSessionMock.h"

ClientMock::ClientMock()
{
}

void ClientMock::Initialize()
{
	const auto network_factory = TcpNetwork::CreateFactory<NetworkMock>();
	const auto session_factory = Session::CreateSessionFactory<ClientSessionMock>();

	_serviceMock = make_unique<ClientServiceMock>(session_factory, network_factory);
	_serviceMock->Initialize();

	_networkMock = network_factory(*_serviceMock);
	_networkMock->SetConnectedMock();

	_serverSession = session_factory();
	_networkMock->AttachSession(_serverSession);
}