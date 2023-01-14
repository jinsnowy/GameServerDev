#include "pch.h"
#include "ClientSession.h"
#include "TcpNetwork.h"

ClientSession::ClientSession(ServiceBase& serviceBase)
	:
	_serviceBase(serviceBase),
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

	auto connector = TcpNetwork::Create(_serviceBase);

	const auto onConnected = [session = shared_from_this()](NetworkPtr network)
	{
		network->AttachSession(session);
	};

	const auto onConnectFailed = [](int32 errorCode)
	{
		LOG_ERROR(L"Connect Failed Error Code : %d, Desc : %s", errorCode, Utils::WSAGetLastErrorMsg(errorCode).c_str());
	};

	connector->ConnectAsync(endPoint, onConnected, onConnectFailed);
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
