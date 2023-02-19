#pragma once

class ServerPacketHandler : public Core::Network::Packet::UserPacketHandler
{
public:
	virtual void onHeartbeat(SessionPtrCRef session, User::Heartbeat pkt) override;
	virtual void onTest(SessionPtrCRef session, User::Test pkt) override;
	virtual void onLoginRequest(SessionPtrCRef session, User::LoginRequest pkt) override;
};