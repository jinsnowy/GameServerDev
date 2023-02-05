#include "pch.h"
#include "Core/Session/Session.h"
#include "Core/Network/Object/TcpNetwork.h"
#include "Core/Network/Handshake/Handshake.h"
#include "Core/Packet/InternalPacketHandler.h"

void packet::InternalPacketHandler::OnCloseBy(NetworkPtrCRef network, PKT_CLOSE_BY* pkt)
{
	LOG_INFO(L"network closed by %s", pkt->reason);
}

void packet::InternalPacketHandler::OnHandshakePacket(NetworkPtrCRef network, CHAR* buffer)
{
	ASSERT_CRASH(network->Handshake() != nullptr);
	network->Handshake()->OnRecv((PacketHeader*)buffer);
}