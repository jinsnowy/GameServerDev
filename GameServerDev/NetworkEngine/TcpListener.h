#pragma once

#include "TcpListenerNetwork.h"

struct ListenerConfig
{
	uint16 bindPort;
	int32  backLog;
	int32  acceptCount;

	NetworkFactory networkFactory;
	OnAcceptFunc   onAccept;
};

class TcpListener : public std::enable_shared_from_this<TcpListener>
{
	friend struct AcceptEvent;
private:
	ServiceBase&   _serviceBase;
	atomic<bool>   _finished;
	ListenerConfig _config;

public:
	TcpListener(ServiceBase& serviceBase, ListenerConfig config);
	
	~TcpListener();

	bool Start();

	void Stop();

private:
	bool ProcessAccept(const NetworkPtr& session);

	void RegisterAccpet();

	TcpListenerNetwork _listenerNetwork;

	vector<NetworkPtr> _acceptNetworks;
};