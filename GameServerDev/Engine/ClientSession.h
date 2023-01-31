#pragma once
#include "Session.h"

class ClientSession : public Session
{
	friend class ClientService;
private:
	ConnectorFactory _connectorFactory;

public:
	ClientSession();

	ClientSession(ConnectorFactory connectorFactory);

	bool Connect(const char* address, uint16 port);

	bool Connect(const EndPoint& endPoint);

	bool Reconnect(const EndPoint& endPoint);

	void ConnectAsync(const EndPoint& endPoint);

	void ReconnectAsync(const EndPoint& endPoint);

protected:
	virtual void OnConnected() override;

	virtual void OnDisconnected() override;

private:
	static void OnNetworkConnectSuccess(SessionPtr session, NetworkPtr network);
	static void OnNetworkConnectFailed(int32 errorCode);
};