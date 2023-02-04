#pragma once

#include "TcpListenerNetwork.h"

class TcpListener : public std::enable_shared_from_this<TcpListener>
{
	friend struct AcceptEvent;
	friend class TcpListenerBuilder;
private:
	ServiceBase&   _serviceBase;
	atomic<bool>   _finished;
	uint16		   _bindPort;
	int32		   _backLog;
	int32		   _acceptCount;
	NetworkFactory _networkFactory;

public:
	TcpListener(ServiceBase& serviceBase);
	
	~TcpListener();

	bool Start();

	void Stop();

private:
	bool ProcessAccept(const NetworkPtr& network);

	void RegisterAccept();

	TcpListenerNetwork _listenerNetwork;
};