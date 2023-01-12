#pragma once
#include "Protocol.h"
#include "PacketHeader.h"
#include "PacketHandler.h"
#include "UserProtocol.pb.h"

enum USERPROTOCOL : int
{
	PKT_HEARTBEAT = 1000,
	PKT_TEST = 1001,
	PKT_LOGIN_REQUEST = 1002,
	PKT_LOGIN_RESPONSE = 1003,
	PKT_ENTER_ROOM_REQUEST = 1004,
	PKT_ENTER_ROOM_RESPONSE = 1005,
	PKT_CLIENT_MOVE_FORWARD = 1006,

	USERPROTOCOL_START = 1000,
	USERPROTOCOL_END = 1006
};
USE_PROTOCOL(UserProtocol::HEARTBEAT);
USE_PROTOCOL(UserProtocol::TEST);
USE_PROTOCOL(UserProtocol::LOGIN_REQUEST);
USE_PROTOCOL(UserProtocol::LOGIN_RESPONSE);
USE_PROTOCOL(UserProtocol::ENTER_ROOM_REQUEST);
USE_PROTOCOL(UserProtocol::ENTER_ROOM_RESPONSE);
USE_PROTOCOL(UserProtocol::CLIENT_MOVE_FORWARD);

class UserProtocolPacketHandler : public PacketHandler
{
public:
	virtual bool IsValidProtocol(int protocol) override
	{
		return protocol >= USERPROTOCOL_START && protocol <= USERPROTOCOL_END;
	}

	virtual void HandleRecv(SessionPtrCRef session, const PacketHeader& header, char* buffer) override
	{
		switch (header.protocol)
		{
		case PKT_HEARTBEAT:
			onHeartbeat(session, Parse<UserProtocol::HEARTBEAT>(buffer, header.size));
			break;
		case PKT_TEST:
			onTest(session, Parse<UserProtocol::TEST>(buffer, header.size));
			break;
		case PKT_LOGIN_REQUEST:
			onLoginRequest(session, Parse<UserProtocol::LOGIN_REQUEST>(buffer, header.size));
			break;
		case PKT_LOGIN_RESPONSE:
			onLoginResponse(session, Parse<UserProtocol::LOGIN_RESPONSE>(buffer, header.size));
			break;
		case PKT_ENTER_ROOM_REQUEST:
			onEnterRoomRequest(session, Parse<UserProtocol::ENTER_ROOM_REQUEST>(buffer, header.size));
			break;
		case PKT_ENTER_ROOM_RESPONSE:
			onEnterRoomResponse(session, Parse<UserProtocol::ENTER_ROOM_RESPONSE>(buffer, header.size));
			break;
		case PKT_CLIENT_MOVE_FORWARD:
			onClientMoveForward(session, Parse<UserProtocol::CLIENT_MOVE_FORWARD>(buffer, header.size));
			break;
		}
	}

public:
	virtual void onHeartbeat(SessionPtrCRef, UserProtocol::HEARTBEAT pkt) {}
	virtual void onTest(SessionPtrCRef, UserProtocol::TEST pkt) {}
	virtual void onLoginRequest(SessionPtrCRef, UserProtocol::LOGIN_REQUEST pkt) {}
	virtual void onLoginResponse(SessionPtrCRef, UserProtocol::LOGIN_RESPONSE pkt) {}
	virtual void onEnterRoomRequest(SessionPtrCRef, UserProtocol::ENTER_ROOM_REQUEST pkt) {}
	virtual void onEnterRoomResponse(SessionPtrCRef, UserProtocol::ENTER_ROOM_RESPONSE pkt) {}
	virtual void onClientMoveForward(SessionPtrCRef, UserProtocol::CLIENT_MOVE_FORWARD pkt) {}
};