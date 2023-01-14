#include "pch.h"
#include "Session.h"
#include "TcpNetwork.h"
#include "InternalPacketHandler.h"

void InternalPacketHandler::OnCloseBy(NetworkPtrCRef network, PKT_CLOSE_BY* pkt)
{
	LOG_INFO(L"network closed by %s", pkt->reason);
}

void InternalPacketHandler::onClientHello(SessionPtrCRef session, PKT_CLIENT_HELLO* pkt)
{
	PKT_SERVER_HELLO hello;
	hello.SessionId = session->GetSessionId();

	session->SendAsync(Serializer::SerializeStruct(hello));
}

void InternalPacketHandler::onServerHello(SessionPtrCRef session, PKT_SERVER_HELLO* pkt)
{
	session->SetSessionId(pkt->SessionId);
}