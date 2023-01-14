#pragma once

enum INTERNAL_PROTOCOL : int
{
	CLIENT_HELLO = -100,
	SERVER_HELLO,
	CLOSE_BY,
	INTERNAL_PROTOCOL_START = CLIENT_HELLO,
	INTERNAL_PROTOCOL_END = CLOSE_BY,
};

struct PKT_CLOSE_BY : PacketHeader
{
	wchar_t reason[256];
	PKT_CLOSE_BY(const wchar_t* _reason)
		:
		PacketHeader(CLOSE_BY)
	{
		ZeroMemory(reason, sizeof(reason));
		lstrcpyW(reason, _reason);
	}
};

struct PKT_CLIENT_HELLO : PacketHeader
{
	SessionID SessionId;
	PKT_CLIENT_HELLO(SessionID _SessionId)
		:
		PacketHeader(CLIENT_HELLO),
		SessionId(_SessionId)
	{}
};

struct PKT_SERVER_HELLO : PacketHeader
{
	SessionID SessionId;
	PKT_SERVER_HELLO()
		:
		PacketHeader(SERVER_HELLO),
		SessionId(0)
	{}
};