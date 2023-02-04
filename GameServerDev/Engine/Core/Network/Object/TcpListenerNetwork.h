#pragma once

#include "../Socket/TcpListenerSocket.h"

class TcpListenerNetwork
{
private:
	TcpListenerSocket  _listenerSocket;

public:
	TcpListenerNetwork(ServiceBase& serviceBase);

	~TcpListenerNetwork();

	bool Initialize();

	bool Bind(uint16 port);

	bool Listen(int32 backLog);

	EndPoint GetBindAddress();

	bool AcceptAsync(ListenerPtr listener, NetworkPtr network, LPVOID bufferPtr);

	bool UpdateAcceptSocket(SOCKET socket);

	void Finish();

	bool IsFinished();
};