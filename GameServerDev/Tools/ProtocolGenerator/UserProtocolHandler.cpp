#include "UserProtocolHandler.h"
DEFINE_PROTOCOL(USERPROTOCOL::HEARTBEAT, HEARTBEAT);
DEFINE_PROTOCOL(USERPROTOCOL::TEST, TEST);
DEFINE_PROTOCOL(USERPROTOCOL::LOGIN_REQUEST, LOGIN_REQUEST);
DEFINE_PROTOCOL(USERPROTOCOL::LOGIN_RESPONSE, LOGIN_RESPONSE);
DEFINE_PROTOCOL(USERPROTOCOL::ENTER_ROOM_REQUEST, ENTER_ROOM_REQUEST);
DEFINE_PROTOCOL(USERPROTOCOL::ENTER_ROOM_RESPONSE, ENTER_ROOM_RESPONSE);