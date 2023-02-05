#include "pch.h"
#include "ClientPacketHandlerMock.h"

void packet::ClientPacketHandlerMock::onTest(SessionPtrCRef session, UserProtocol::Test pkt)
{
}

void packet::ClientPacketHandlerMock::onLoginResponse(SessionPtrCRef session, UserProtocol::LoginResponse pkt)
{
}
