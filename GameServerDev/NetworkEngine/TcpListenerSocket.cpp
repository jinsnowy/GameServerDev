#include "pch.h"
#include "TcpListenerSocket.h"

TcpListenerSocket::TcpListenerSocket(ServiceBase& service)
	:
	TcpSocket(service)
{
}

bool TcpListenerSocket::Bind(uint16 port)
{
	_bindEndPoint = EndPoint("127.0.0.1", port);
	return NetUtils::Bind(_socket, _bindEndPoint);
}

bool TcpListenerSocket::Listen(int32 backLog)
{
	return NetUtils::Listen(_socket, backLog);
}

bool TcpListenerSocket::SetUpdateAcceptSocket(SOCKET acceptSocket)
{
	return NetUtils::SetUpdateAcceptSocket(acceptSocket, _socket);
}