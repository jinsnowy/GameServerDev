#pragma once

#include "protocol/UserProtocolHandler.h"

namespace packet
{
	class ServerPacketHandler : public UserProtocolPacketHandler
	{
	public:
		virtual void onHeartbeat(SessionPtrCRef session, UserProtocol::Heartbeat pkt) override;
		virtual void onTest(SessionPtrCRef session, UserProtocol::Test pkt) override;
		virtual void onCreateAccountRequest(SessionPtrCRef, UserProtocol::CreateAccountRequest pkt) override;
		virtual void onLoginRequest(SessionPtrCRef session, UserProtocol::LoginRequest pkt) override;
	};
}
