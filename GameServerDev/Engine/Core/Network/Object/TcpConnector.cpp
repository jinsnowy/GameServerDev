#include "pch.h"
#include "TcpConnector.h"
#include "TcpNetwork.h"

#include "../Session/ClientSession.h"
#include "../Service/ServiceBase.h"

namespace Core {
	namespace Network {
		static void OnNetworkConnectSuccess(shared_ptr<TcpConnector> connector, shared_ptr<TcpNetwork> network);
		static void OnNetworkConnectFailed(int32 errorCode);

		TcpConnector::TcpConnector(shared_ptr<TcpNetwork> network)
			:
			_network(network)
		{
		}

		void TcpConnector::Connect(EndPoint endPoint)
		{
			if (_network)
			{
				const auto connect_success = [connector = shared_from_this()](shared_ptr<TcpNetwork> network)
				{
					OnNetworkConnectSuccess(connector, network);
				};

				LOG_INFO(L"[TcpConnector] connecting to %s ...", endPoint.ToString().c_str());

				_network->ConnectAsync(endPoint, connect_success, OnNetworkConnectFailed);

				int waitCount = 0;
				while (_network->IsConnected() == false && ++waitCount < 10)
				{
					std::this_thread::sleep_for(1s);
				}

				if (waitCount == 5) {
					LOG_INFO(L"[TcpConnector] failed to connect", endPoint.ToString().c_str());
				}
			}
		}

		void OnNetworkConnectSuccess(shared_ptr<TcpConnector> connector, shared_ptr<TcpNetwork> network)
		{
			LOG_INFO(L"Connect Success");
		}

		void OnNetworkConnectFailed(int32 errorCode)
		{
			LOG_ERROR(L"Connect Failed Error Code : %d, Desc : %s", errorCode, SystemUtils::WSAGetLastErrorMsg(errorCode).c_str());
		}
	}
}