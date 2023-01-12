#include "stdafx.h"
#include "ServerPacketHandler.h"
#include "protocol\UserProtocol.pb.h"
#include "Session.h"
#include "Room.h"
#include "UserSession.h"

void ServerPacketHandler::onHeartbeat(SessionPtrCRef session, UserProtocol::HEARTBEAT pkt)
{
}

void ServerPacketHandler::onTest(SessionPtrCRef session, UserProtocol::TEST pkt)
{
	LOG_INFO("Session(%lld) : %s", session->GetSessionId(), pkt.text().c_str());

	//auto player = session->GetShared<UserSession>()->GetPlayer();

	//Utils::SharedGlobal<Room>()->Enqueue(&Room::Broadcast, BufferSegment::Serialize(pkt));
}

void ServerPacketHandler::onLoginRequest(SessionPtrCRef session, UserProtocol::LOGIN_REQUEST pkt)
{
	session->GetShared<UserSession>()->SetPlayer(pkt.player());

	UserProtocol::LOGIN_RESPONSE response;
	*response.mutable_player() = pkt.player();

	session->SendAsync(BufferSegment::Serialize(response));
}

void ServerPacketHandler::onEnterRoomRequest(SessionPtrCRef session, UserProtocol::ENTER_ROOM_REQUEST pkt)
{
	auto player = session->GetShared<UserSession>()->GetPlayer();

	Utils::SharedGlobal<Room>()->Enqueue(&Room::Enter, player);

	UserProtocol::ENTER_ROOM_RESPONSE response;
	response.set_id(0);
	session->SendAsync(BufferSegment::Serialize(response));
}
