#include "pch.h"
#include "ClientMock.h"
#include "ClientSessionMock.h"

ClientMock::ClientMock()
	:
	_sessionManagerMock(Session::CreateSessionFactory<ClientSessionMock>()),
	_serviceMock(_sessionManagerMock)
{
}

void ClientMock::Initialize()
{
	_networkMock = make_shared<NetworkMock>(_serviceMock);
	_networkMock->SetConnectedMock();

	_serverSession = _sessionManagerMock.NewSession();
	_networkMock->AttachSession(_serverSession);
}
