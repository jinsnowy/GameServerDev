#include "pch.h"
#include "NetworkMock.h"

NetworkMock::NetworkMock(ServiceBase& serviceBase)
	:
	TcpNetwork(serviceBase)
{
}

void NetworkMock::SetConnectedMock()
{
	TcpNetwork::SetConnected(EndPoint("127.0.0.1", 9910));
}

void NetworkMock::SetDisconnectedMock()
{
	TcpNetwork::SetDisconnected();
}
