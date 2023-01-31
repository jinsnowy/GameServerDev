#pragma once

#include "protocol/UserProtocolHandler.h"

namespace packet
{
	class ClientPacketHandler : public UserProtocolPacketHandler
	{
	protected:
		virtual void onTest(SessionPtrCRef session, UserProtocol::Test pkt);
		virtual void onLoginResponse(SessionPtrCRef session, UserProtocol::LoginResponse pkt) override;
	};
}
