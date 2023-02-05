#include "pch.h"
#include "ServerMock.h"
#include "ServerSessionMock.h"

ServerMock::ServerMock()
	:
	_sessionManagerMock(Session::CreateSessionFactory<ServerSessionMock>()),
	_serviceMock(_sessionManagerMock)
{
}

void ServerMock::Initialize()
{
	_networkMock = make_shared<NetworkMock>(_serviceMock);
	_networkMock->SetConnectedMock();

	_serverSession = _sessionManagerMock.NewSession();
	_networkMock->AttachSession(_serverSession);
}
