#include "pch.h"
#include "TcpListenerBuilder.h"
#include "TcpListener.h"

TcpListenerBuilder::TcpListenerBuilder()
	:
	_bindPort(9190),
	_backLog(100),
	_acceptCount(10)
{
}

TcpListenerBuilder& TcpListenerBuilder::Port(uint16 port)
{
	_bindPort = port;
	return *this;
}

TcpListenerBuilder& TcpListenerBuilder::BackLog(int32 backLog)
{
	_backLog = backLog;
	return *this;
}

TcpListenerBuilder& TcpListenerBuilder::AcceptCount(int32 acceptCount)
{
	_acceptCount = acceptCount;
	return *this;
}

TcpListenerBuilder& TcpListenerBuilder::_NetworkFactory(NetworkFactory networkFactory)
{
	_networkFactory = networkFactory;
	return *this;
}

shared_ptr<class TcpListener> TcpListenerBuilder::Build(ServiceBase& serviceBase)
{
	auto listener = make_shared<TcpListener>(serviceBase);
	listener->_bindPort = _bindPort;
	listener->_backLog = _backLog;
	listener->_acceptCount = _acceptCount;
	listener->_networkFactory = _networkFactory;

	return listener;
}
