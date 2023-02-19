#pragma once

class ClientPacketHandler : public Core::Network::Packet::UserPacketHandler
{
protected:
	virtual void onTest(SessionPtrCRef session, User::Test pkt);
	virtual void onLoginResponse(SessionPtrCRef session, User::LoginResponse pkt) override;
};