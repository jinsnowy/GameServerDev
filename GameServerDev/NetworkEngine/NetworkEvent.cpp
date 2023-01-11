#include "pch.h"
#include "NetworkEvent.h"
#include "TcpNetwork.h"

RecvEvent::RecvEvent(shared_ptr<TcpNetwork> networkIn)
	:
	network(networkIn)
{}

void RecvEvent::operator()(int32 errorCode, DWORD recvBytes)
{
	if (recvBytes == 0)
	{
		network->disconnectOnError("recv 0");
		return;
	}

	if (errorCode != 0)
	{
		network->handleError(errorCode);
		return;
	}

	network->recv(recvBytes);
	network->registerRecv();
}

void SendEvent::operator()(int32 errorCode, DWORD writeBytes)
{
	if (writeBytes == 0)
	{
		network->disconnectOnError("write 0");
		return;
	}

	if (errorCode != 0)
	{
		network->handleError(errorCode);
		return;
	}

	network->flush();
}

SendEvent::SendEvent(shared_ptr<TcpNetwork> networkIn, std::vector<BufferSegment>&& segments)
	:
	network(networkIn),
	segmentHolder(segments)
{}

void SendEvent::operator()(int32 errorCode, DWORD writeBytes)
{
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

	network->setDisconnected();
}
