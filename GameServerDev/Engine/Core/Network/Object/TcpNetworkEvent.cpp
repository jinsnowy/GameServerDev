#include "pch.h"

#include "TcpNetworkEvent.h"
#include "TcpNetwork.h"
#include "TcpListener.h"
#include "../Buffer/BufferSegment.h"

namespace Core {
	namespace Network {
		using namespace IO;
		using namespace Buffer;

		RecvEvent::RecvEvent(shared_ptr<TcpNetwork> networkIn)
			:
			network(networkIn)
		{}

		void RecvEvent::operator()(int32 errorCode, DWORD recvBytes)
		{
			if (recvBytes == 0)
			{
				network->CloseBy();
				return;
			}

			if (errorCode != 0)
			{
				network->HandleError(errorCode, IoType::IO_READ);
				return;
			}

			network->Recv(recvBytes);
			network->RegisterRecv();
		}

		SendEvent::SendEvent(shared_ptr<TcpNetwork> networkIn, std::vector<BufferSegment>&& segments)
			:
			network(networkIn),
			segmentHolder(segments)
		{}

		void SendEvent::operator()(int32 errorCode, DWORD writeBytes)
		{
			if (writeBytes == 0)
			{
				network->CloseBy();
				return;
			}

			if (errorCode != 0)
			{
				network->HandleError(errorCode, IoType::IO_WRITE);
				return;
			}

			network->RegisterSend();
		}

		ConnectEvent::ConnectEvent(shared_ptr<TcpNetwork> networkIn, EndPoint _endPoint, OnConnectFunc _onConnected, OnConnectFailFunc _onConnectFailed)
			:
			network(networkIn), endPoint(_endPoint), onConnected(_onConnected), onConnectFailed(_onConnectFailed)
		{}

		void ConnectEvent::operator()(int32 errorCode, DWORD)
		{
			if (errorCode != 0)
			{
				onConnectFailed(errorCode);

				return;
			}

			network->SetConnected(endPoint);
			network->Start();

			onConnected(network);
		}

		DisconnectEvent::DisconnectEvent(shared_ptr<TcpNetwork> networkIn)
			:
			network(networkIn)
		{
		}

		void DisconnectEvent::operator()(int32 errorCode, DWORD)
		{
			if (errorCode != 0)
			{
				LOG_ERROR(L"disconnect error : %s", get_last_err_msg());
			}

			network->SetDisconnected();
		}

		AcceptEvent::AcceptEvent(shared_ptr<TcpListener> _listenerPtr, shared_ptr<TcpNetwork> _networkPtr)
			:
			listenerPtr(_listenerPtr), networkPtr(_networkPtr)
		{}

		void AcceptEvent::operator()(int32 errorCode, DWORD)
		{
			if (errorCode != 0)
			{
				LOG_ERROR(L"OnAccept Error : %s", get_last_err_msg_code(errorCode));
				listenerPtr->RegisterAccept();
				return;
			}

			LOG_INFO(L"OnAccept");

			if (!listenerPtr->ProcessAccept(networkPtr))
			{
				LOG_ERROR(L"cannot process accept");
				listenerPtr->RegisterAccept();
				return;
			}

			listenerPtr->RegisterAccept();
		}
	}
}