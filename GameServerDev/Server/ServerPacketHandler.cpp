#include "stdafx.h"
#include "ServerPacketHandler.h"

#include "Engine/Core/Session/Session.h"

#include "UserSession.h"

using namespace packet;

void ServerPacketHandler::onHeartbeat(SessionPtrCRef session, User::Heartbeat pkt)
{
}

void ServerPacketHandler::onTest(SessionPtrCRef session, User::Test pkt)
{
	static map<SessionID, int> counter;
	if (counter.find(session->GetSessionId()) == counter.end()) {
		counter[session->GetSessionId()] = 0;
	}

	string text_str = pkt.text();
	wstring text_str_w = StringUtils::ToWide(text_str);

	int count = counter[session->GetSessionId()]++;
	if (count % 10 == 0) {
		LOG_INFO(L"Session (%lld) : %s count %d", session->GetSessionId(), text_str_w.c_str(), count);
	}

	// auto player = session->GetShared<UserSession>()->GetPlayer();

	// Utils::SharedGlobal<Room>()->Enqueue(&Room::Broadcast, BufferSegment::Serialize(pkt));
}

void ServerPacketHandler::onLoginRequest(SessionPtrCRef session, User::LoginRequest pkt)
{

}

