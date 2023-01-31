#include "stdafx.h"
#include "UserSession.h"
#include "TcpNetwork.h"
#include "ServerPacketHandler.h"

UserSession::UserSession()
{
}

void UserSession::OnConnected()
{
	ServerSession::OnConnected();
}