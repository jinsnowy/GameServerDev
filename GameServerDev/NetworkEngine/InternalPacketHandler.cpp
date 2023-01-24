#include "pch.h"
#include "Session.h"
#include "TcpNetwork.h"
#include "Handshake.h"
#include "InternalPacketHandler.h"

void InternalPacketHandler::OnCloseBy(NetworkPtrCRef network, PKT_CLOSE_BY* pkt)
{
	LOG_INFO(L"network closed by %s", pkt->reason);
}

void InternalPacketHandler::OnHandshakePacket(NetworkPtrCRef network, CHAR* buffer)
{
	ASSERT_CRASH(network->Handshake() != nullptr);
	network->Handshake()->OnRecv((PacketHeader*)buffer);
}