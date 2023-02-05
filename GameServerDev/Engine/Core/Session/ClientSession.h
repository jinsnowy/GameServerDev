#pragma once
#include "Session.h"

class ClientSession : public Session
{
public:
	ClientSession();

	bool Connect(const char* address, uint16 port);

	bool Connect(const EndPoint& endPoint);

	bool Reconnect(const EndPoint& endPoint);

	void ConnectAsync(const EndPoint& endPoint);

	void ReconnectAsync(const EndPoint& endPoint);

protected:
	virtual void OnConnected() override;

	virtual void OnDisconnected() override;
};