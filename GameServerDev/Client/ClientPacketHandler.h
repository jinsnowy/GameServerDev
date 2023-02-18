#pragma once

namespace packet
{
	class ClientPacketHandler : public UserPacketHandler
	{
	protected:
		virtual void onTest(SessionPtrCRef session, User::Test pkt);
		virtual void onLoginResponse(SessionPtrCRef session, User::LoginResponse pkt) override;
	};
}
