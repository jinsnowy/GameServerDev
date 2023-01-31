#include "stdafx.h"
#include "ClientPacketHandler.h"
#include "PlayerSession.h"

using namespace packet;

void ClientPacketHandler::onTest(SessionPtrCRef session, UserProtocol::Test pkt)
{
	//LOG_INFO("%s", pkt.text().c_str());
}

void ClientPacketHandler::onLoginResponse(SessionPtrCRef session, UserProtocol::LoginResponse pkt)
{
	/*session->GetShared<PlayerSession>()->SetPlayer(pkt.player());

	UserProtocol::ENTER_ROOM_REQUEST request;
	session->GetShared<PlayerSession>()->SendAsync(Serializer::SerializeProtoBuf(request));*/
}
