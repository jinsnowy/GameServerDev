#include "pch.h"
#include "NetworkEvent.h"

#include "TcpNetwork.h"
#include "TcpListener.h"

RecvEvent::RecvEvent(shared_ptr<TcpNetwork> networkIn)
	:
	network(networkIn)
{}

void RecvEvent::operator()(int32 errorCode, DWORD recvBytes)
{
	if (recvBytes == 0)
	{
		network->DisconnectOnError("recv 0");
		return;
	}

	if (errorCode != 0)
	{
		network->HandleError(errorCode);
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
		network->DisconnectOnError("write 0");
		return;
	}

	if (errorCode != 0)
	{
		network->HandleError(errorCode);
		return;
	}

	network->Flush();
}

ConnectEvent::ConnectEvent(shared_ptr<TcpNetwork> networkIn, EndPoint _endPoint)
	: 
	network(networkIn), endPoint(_endPoint)
{}

void ConnectEvent::operator()(int32 errorCode, DWORD)
{
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
		LOG_ERROR("disconnect error : %s", get_last_err_msg());
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
		LOG_ERROR("OnAccept Error : %s", get_last_err_msg_code(errorCode));
		listenerPtr->RegisterAccpet();
		return;
	}

	if (!listenerPtr->ProcessAccept(networkPtr))
	{
		LOG_ERROR("cannot process accept");
		listenerPtr->RegisterAccpet();
		return;
	}

	listenerPtr->RegisterAccpet();
}