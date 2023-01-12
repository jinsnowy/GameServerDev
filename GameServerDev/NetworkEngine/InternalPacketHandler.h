#pragma once
#include "PacketHandler.h"
#include "InternalProtocol.h"

class InternalPacketHandler : public PacketHandler
{
public:
	virtual bool IsValidProtocol(int32 protocol) override
	{
		return protocol >= INTERNAL_PROTOCOL_START && protocol <= INTERNAL_PROTOCOL_END;
	}

	virtual void HandleRecv(NetworkPtrCRef network, const PacketHeader& header, CHAR* buffer) override
	{
	}

private:
	template<typename T>
	T* interpret(CHAR* buffer) { return reinterpret_cast<T*>(buffer); }

	static void onClientHello(SessionPtrCRef session, PKT_CLIENT_HELLO* pkt);
	static void onServerHello(SessionPtrCRef session, PKT_SERVER_HELLO* pkt);
};