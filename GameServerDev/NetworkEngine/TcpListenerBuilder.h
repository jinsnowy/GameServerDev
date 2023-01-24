#pragma once

class TcpListenerBuilder
{
private:
	uint16		   _bindPort;
	int32		   _backLog;
	int32		   _acceptCount;
	NetworkFactory _networkFactory;

public:
	TcpListenerBuilder();

	TcpListenerBuilder& Port(uint16 port);
	TcpListenerBuilder& BackLog(int32 backLog);
	TcpListenerBuilder& AcceptCount(int32 acceptCount);
	TcpListenerBuilder& _NetworkFactory(NetworkFactory networkFactory);

	shared_ptr<class TcpListener> Build(ServiceBase& serviceBase);
};

