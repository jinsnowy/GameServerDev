#include "pch.h"
#include "ServerPacketHandler.h"
#include "Engine/Core/Session/Session.h"
using namespace packet;

void ServerPacketHandler::onHeartbeat(SessionPtrCRef session, UserProtocol::Heartbeat pkt)
{
}

void ServerPacketHandler::onTest(SessionPtrCRef session, UserProtocol::Test pkt)
{
}

void ServerPacketHandler::onLoginRequest(SessionPtrCRef session, UserProtocol::LoginRequest pkt)
{
}
