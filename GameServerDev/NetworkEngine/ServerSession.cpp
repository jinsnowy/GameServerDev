#include "pch.h"
#include "ServerSession.h"

ServerSession::ServerSession()
	:
	Session()
{
}

void ServerSession::OnConnected()
{
	Session::OnConnected();
}

void ServerSession::OnDisconnected()
{
	Session::OnDisconnected();
}
