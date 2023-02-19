#include "pch.h"
#include "TcpListenerBuilder.h"
#include "TcpListener.h"

namespace Core {
	namespace Network {
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
			return self();
		}

		TcpListenerBuilder& TcpListenerBuilder::AcceptCount(int32 acceptCount)
		{
			_acceptCount = acceptCount;
			return self();
		}

		TcpListenerBuilder& TcpListenerBuilder::Factory(NetworkFactory networkFactory)
		{
			_networkFactory = networkFactory;
			return self();
		}

		shared_ptr<class TcpListener> TcpListenerBuilder::Build(Service::ServiceBase& serviceBase)
		{
			auto listener = make_shared<TcpListener>(serviceBase);
			listener->_bindPort = _bindPort;
			listener->_backLog = _backLog;
			listener->_acceptCount = _acceptCount;
			listener->_networkFactory = _networkFactory;

			return listener;
		}
	}
}