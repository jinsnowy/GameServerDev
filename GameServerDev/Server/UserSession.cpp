#include "stdafx.h"
#include "UserSession.h"
#include "ServerPacketHandler.h"

UserSession::UserSession()
{
}

void UserSession::OnConnected()
{
	ServerSession::OnConnected();
}