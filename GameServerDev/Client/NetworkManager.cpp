#include "stdafx.h"
#include "NetworkManager.h"

void NetworkManager::OnConnected()
{
	ClientSession::OnConnected();
}

void NetworkManager::OnDisconnected()
{
	ClientSession::OnDisconnected();
}
