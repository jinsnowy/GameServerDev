#include "pch.h"
#include "ClientSession.h"
#include "Core/Network/Object/TcpNetwork.h"

ClientSession::ClientSession()
	:
	Session()
{
}

ClientSession::ClientSession(ConnectorFactory connectorFactory)
	:
	_connectorFactory(connectorFactory),
	Session()
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

	auto connector = _connectorFactory();

	connector->ConnectAsync(endPoint, 
		std::bind(OnNetworkConnectSuccess, shared_from_this(), std::placeholders::_1),
		OnNetworkConnectFailed);
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
	Session::OnConnected();
}

void ClientSession::OnDisconnected()
{
	Session::OnDisconnected();
}

void ClientSession::OnNetworkConnectSuccess(SessionPtr session, NetworkPtr network)
{
	network->AttachSession(session);
}

void ClientSession::OnNetworkConnectFailed(int32 errorCode)
{
	LOG_ERROR(L"Connect Failed Error Code : %d, Desc : %s", errorCode, SystemUtils::WSAGetLastErrorMsg(errorCode).c_str());
}
