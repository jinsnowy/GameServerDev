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
	static map<SessionID, int> counter;
	if (counter.find(session->GetSessionId()) == counter.end()) {
		counter[session->GetSessionId()] = 0;
	}

	int count = counter[session->GetSessionId()]++;
	if (count % 10 == 0) {
		LOG_INFO(L"Session (%lld) : %S", session->GetSessionId(), pkt.text().c_str());
	}

	// auto player = session->GetShared<UserSession>()->GetPlayer();

	// Utils::SharedGlobal<Room>()->Enqueue(&Room::Broadcast, BufferSegment::Serialize(pkt));
}

void ServerPacketHandler::onLoginRequest(SessionPtrCRef session, UserProtocol::LOGIN_REQUEST pkt)
{
	session->GetShared<UserSession>()->SetPlayer(pkt.player());

	UserProtocol::LOGIN_RESPONSE response;
	*response.mutable_player() = pkt.player();

	session->SendAsync(Serializer::SerializeProtoBuf(response));
}

void ServerPacketHandler::onEnterRoomRequest(SessionPtrCRef session, UserProtocol::ENTER_ROOM_REQUEST pkt)
{
	auto player = session->GetShared<UserSession>()->GetPlayer();

	Utils::SharedGlobal<Room>()->Enqueue(&Room::Enter, player);

	UserProtocol::ENTER_ROOM_RESPONSE response;
	response.set_id(0);
	session->SendAsync(Serializer::SerializeProtoBuf(response));
}
