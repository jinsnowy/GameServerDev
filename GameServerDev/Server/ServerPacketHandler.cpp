#include "stdafx.h"
#include "ServerPacketHandler.h"

#include "Engine/Core/Session/Session.h"

#include "UserSession.h"

using namespace packet;

void ServerPacketHandler::onHeartbeat(SessionPtrCRef session, UserProtocol::Heartbeat pkt)
{
}

void ServerPacketHandler::onTest(SessionPtrCRef session, UserProtocol::Test pkt)
{
	static map<SessionID, int> counter;
	if (counter.find(session->GetSessionId()) == counter.end()) {
		counter[session->GetSessionId()] = 0;
	}

	int count = counter[session->GetSessionId()]++;
	if (count % 10 == 0) {
		LOG_INFO(L"Session (%lld) : %S count %d", session->GetSessionId(), pkt.text().c_str(), count);
	}

	// auto player = session->GetShared<UserSession>()->GetPlayer();

	// Utils::SharedGlobal<Room>()->Enqueue(&Room::Broadcast, BufferSegment::Serialize(pkt));
}

void ServerPacketHandler::onLoginRequest(SessionPtrCRef session, UserProtocol::LoginRequest pkt)
{

}

