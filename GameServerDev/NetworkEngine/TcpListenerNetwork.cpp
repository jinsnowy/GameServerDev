#include "pch.h"
#include "TcpListenerNetwork.h"
#include "TcpNetwork.h"
#include "NetworkEvent.h"

TcpListenerNetwork::TcpListenerNetwork(ServiceBase& serviceBase)
	:
	_listenerSocket(serviceBase)
{
}

TcpListenerNetwork::~TcpListenerNetwork()
{
	Finish();
}

bool TcpListenerNetwork::Initialize()
{
	if (!_listenerSocket.SetReuseAddress(true))
	{
		LOG_ERROR("reuse error : %s", get_last_err_msg());
		return false;
	}

	if (!_listenerSocket.SetLinger(0, 0))
	{
		LOG_ERROR("set no linger error : %s", get_last_err_msg());
		return false;
	}

	return true;
}

bool TcpListenerNetwork::Bind(uint16 port)
{
	if (!_listenerSocket.Bind(port))
	{
		LOG_ERROR("bind %hd error : %s", port, get_last_err_msg());
		return false;
	}

	return true;
}

bool TcpListenerNetwork::Listen(int32 backLog)
{
	if (!_listenerSocket.Listen(backLog))
	{
		LOG_ERROR("listen error : %s", get_last_err_msg());
		return false;
	}

	return true;
}

EndPoint TcpListenerNetwork::GetBindAddress()
{
	return _listenerSocket.GetAddress();
}

bool TcpListenerNetwork::AcceptAsync(ListenerPtr listener, NetworkPtr network, LPVOID bufferPtr)
{
	return _listenerSocket.AcceptAsync(network->GetSocket(), bufferPtr, AcceptEvent(listener, network));
}

bool TcpListenerNetwork::UpdateAcceptSocket(SOCKET socket)
{
	return _listenerSocket.SetUpdateAcceptSocket(socket);
}

void TcpListenerNetwork::Finish()
{
	_listenerSocket.Dispose("Finish");
}

bool TcpListenerNetwork::IsFinished()
{
	return _listenerSocket.IsDisposed();
}
