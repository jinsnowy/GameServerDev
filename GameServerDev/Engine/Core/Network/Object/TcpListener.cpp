#include "pch.h"
#include "TcpListener.h"
#include "TcpNetwork.h"
#include "Core/Network/Session/SessionManager.h"
#include "Core/Network/Service/ServiceBase.h"

namespace Core {
	namespace Network {
		TcpListener::TcpListener(Service::ServiceBase& serviceBase)
			:
			_serviceBase(serviceBase),
			_finished(false),
			_listenerNetwork(serviceBase),
			_acceptCount(10),
			_bindPort(9190),
			_backLog(10)
		{
		}

		TcpListener::~TcpListener()
		{
			Stop();
		}

		bool TcpListener::Start()
		{
			if (!_listenerNetwork.Initialize()) {
				return false;
			}

			if (!_listenerNetwork.Bind(_bindPort)) {
				return false;
			}

			if (!_listenerNetwork.Listen(_backLog)) {
				return false;
			}

			LOG_INFO(L"Accept Count %d", _acceptCount);

			for (int32 i = 0; i < _acceptCount; ++i) {
				RegisterAccept();
			}

			LOG_INFO(L"Listen... %s", _listenerNetwork.GetBindAddress().ToString().c_str());

			return true;
		}

		void TcpListener::Stop()
		{
			_listenerNetwork.Finish();
		}

		bool TcpListener::ProcessAccept(const NetworkPtr& network)
		{
			if (!_listenerNetwork.UpdateAcceptSocket(network->GetSocket()))
			{
				LOG_ERROR(L"cannot update socket : %s", get_last_err_msg());
				return false;
			}

			EndPoint endPoint;
			if (!NetUtils::GetEndPoint(network->GetSocket(), endPoint))
			{
				LOG_ERROR(L"cannot get address : %s", get_last_err_msg());
				return false;
			}

			network->SetConnected(endPoint);
			network->Start();

			return true;
		}

		void TcpListener::RegisterAccept()
		{
			ENQUEUE(TcpListener, [](shared_ptr<TcpListener> listener)
				{
					NetworkPtr network = listener->_networkFactory(listener->_serviceBase);
					LPVOID bufferPtr = network->GetRecvBuffer().GetBufferPtr();

					if (!listener->_listenerNetwork.AcceptAsync(listener, network, bufferPtr))
					{
						LOG_ERROR(L"accept error : %s", get_last_err_msg());
					}
				});
		}
	}
}