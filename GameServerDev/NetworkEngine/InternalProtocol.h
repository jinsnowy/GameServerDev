#pragma once

enum INTERNAL_PROTOCOL : int
{
	CLIENT_HELLO = -100,
	SERVER_HELLO,
	AUTH_REQUEST,
	AUTH_RESPONSE,
	CLOSE_BY,
	INTERNAL_PROTOCOL_START = CLIENT_HELLO,
	INTERNAL_PROTOCOL_END = CLOSE_BY,
};

struct PKT_CLOSE_BY : PacketHeader
{
	StringBuffer reason;
	PKT_CLOSE_BY(const wchar_t* _reason)
		:
		PacketHeader(CLOSE_BY)
	{
		reason.Set(_reason);
	}
};

struct PKT_CLIENT_HELLO : PacketHeader
{
	PKT_CLIENT_HELLO()
		:
		PacketHeader(CLIENT_HELLO)
	{}
};

struct PKT_SERVER_HELLO : PacketHeader
{
	StringBuffer uuid;
	PKT_SERVER_HELLO()
		:
		PacketHeader(SERVER_HELLO),
		uuid{}
	{}
};

struct PKT_AUTH_REQUEST : PacketHeader
{
	StringBuffer uuid;
	PKT_AUTH_REQUEST()
		:
		PacketHeader(AUTH_REQUEST)
	{
	}
};

struct PKT_AUTH_RESPONSE: PacketHeader
{
	bool success;
	StringBuffer reason;
	PKT_AUTH_RESPONSE()
		:
		PacketHeader(AUTH_RESPONSE)
	{}
};