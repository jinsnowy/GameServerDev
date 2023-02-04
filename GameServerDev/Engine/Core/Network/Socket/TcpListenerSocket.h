#pragma once

#include "TcpSocket.h"
#include "../IO/IoEvent.h"

class TcpListenerSocket : public TcpSocket
{
private:
	EndPoint _bindEndPoint;

public:
	TcpListenerSocket(ServiceBase& service);

	EndPoint GetAddress() { return _bindEndPoint; }

	bool Bind(uint16 port);

	bool Listen(int32 backLog = SOMAXCONN);

	bool SetUpdateAcceptSocket(SOCKET acceptSocket);

	template<typename OnAcceptCallback>
	bool AcceptAsync(SOCKET acceptSocket, LPVOID recvBuf, OnAcceptCallback&& onAccept)
	{
		IoEvent* ioEvent = MakeAcceptTask(std::forward<OnAcceptCallback>(onAccept));

		if (!NetUtils::AcceptAsync(_socket, acceptSocket, recvBuf, ioEvent))
		{
			ioEvent->release();

			return false;
		}

		return true;
	}

	ServiceBase& GetServiceBase() { return TcpSocket::_service; }
};