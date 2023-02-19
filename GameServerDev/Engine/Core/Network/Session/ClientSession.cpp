#include "pch.h"
#include "ClientSession.h"
#include "Core/Network/Object/TcpNetwork.h"

namespace Core {
	namespace Network {
		namespace Session {
			static void OnNetworkConnectSuccess(shared_ptr<ClientSession> session, shared_ptr<TcpNetwork> network);
			static void OnNetworkConnectFailed(int32 errorCode);

			ClientSession::ClientSession()
				:
				SessionBase()
			{
			}

			bool ClientSession::Connect(const char* address, uint16 port)
			{
				return Connect(EndPoint(address, port));
			}

			bool ClientSession::Connect(const EndPoint& endPoint)
			{
				if (IsConnected())
				{
					LOG_INFO(L"already connected");
					return true;
				}

				int count = 0;
				while (!IsConnected() && ++count < 10)
				{
					std::this_thread::sleep_for(200ms);
				}

				return IsConnected();
			}

			bool ClientSession::Reconnect(const EndPoint& endPoint)
			{
				if (IsConnected())
				{
					Disconnect();
				}

				LOG_INFO(L"reconnect ...");

				return Connect(endPoint);
			}

			void ClientSession::ConnectAsync(const EndPoint& endPoint)
			{
				if (IsConnected())
				{
					LOG_INFO(L"already connected");
					return;
				}

				if (_network)
				{
					const auto connect_success = [session = GetShared<ClientSession>()](shared_ptr<TcpNetwork> network)
					{
						OnNetworkConnectSuccess(session, network);
					};

					_network->ConnectAsync(endPoint, connect_success, OnNetworkConnectFailed);
				}
			}

			void ClientSession::ReconnectAsync(const EndPoint& endPoint)
			{
				if (IsConnected())
				{
					DisconnectAsync();
				}

				return ConnectAsync(endPoint);
			}

			void ClientSession::OnConnected()
			{
				SessionBase::OnConnected();
			}

			void ClientSession::OnDisconnected()
			{
				SessionBase::OnDisconnected();
			}


			void OnNetworkConnectSuccess(shared_ptr<ClientSession> session, shared_ptr<TcpNetwork> network)
			{
				network->AttachSession(session);
			}

			void OnNetworkConnectFailed(int32 errorCode)
			{
				LOG_ERROR(L"Connect Failed Error Code : %d, Desc : %s", errorCode, SystemUtils::WSAGetLastErrorMsg(errorCode).c_str());
			}
		}
	}
}