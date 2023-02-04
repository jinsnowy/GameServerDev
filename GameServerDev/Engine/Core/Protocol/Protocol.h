#pragma once

#define USE_PROTOCOL(p)\
template<>\
int packet::Protocol::GetProtocol<p>();

#define DEFINE_PROTOCOL(p, v)\
template<>\
int packet::Protocol::GetProtocol<p>() { return v; }

namespace packet
{
	class Protocol
	{
	public:
		template<typename T>
		static int GetProtocol() { return 0; }
	};
}