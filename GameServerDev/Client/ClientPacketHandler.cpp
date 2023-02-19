#include "stdafx.h"
#include "ClientPacketHandler.h"

void ClientPacketHandler::onTest(SessionPtrCRef session, User::Test pkt)
{
	//LOG_INFO("%s", pkt.text().c_str());
}

void ClientPacketHandler::onLoginResponse(SessionPtrCRef session, User::LoginResponse pkt)
{
	/*session->GetShared<PlayerSession>()->SetPlayer(pkt.player());

	UserProtocol::ENTER_ROOM_REQUEST request;
	session->GetShared<PlayerSession>()->SendAsync(Serializer::SerializeProtoBuf(request));*/
}
