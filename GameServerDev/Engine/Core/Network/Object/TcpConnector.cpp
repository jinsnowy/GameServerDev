#include "pch.h"
#include "TcpConnector.h"
#include "../../Session/ClientSession.h"
#include "TcpNetwork.h"

static void OnNetworkConnectSuccess(shared_ptr<TcpConnector> connector, shared_ptr<TcpNetwork> network);
static void OnNetworkConnectFailed(int32 errorCode);

TcpConnector::TcpConnector(shared_ptr<ClientSession> session, shared_ptr<TcpNetwork> network)
	:
	_target_session(session),
	_network(network)
{
}

shared_ptr<Session> TcpConnector::Release()
{
	auto session = _target_session;
	_target_session = nullptr;
	return session;
}

void TcpConnector::Connect(EndPoint endPoint)
{
	if (_network)
	{
		const auto connect_success = [connector = shared_from_this()](shared_ptr<TcpNetwork> network)
		{
			OnNetworkConnectSuccess(connector, network);
		};

		_network->ConnectAsync(endPoint, connect_success, OnNetworkConnectFailed);
	}
}

void OnNetworkConnectSuccess(shared_ptr<TcpConnector> connector, shared_ptr<TcpNetwork> network)
{
	network->AttachSession(connector->Release());
}

void OnNetworkConnectFailed(int32 errorCode)
{
	LOG_ERROR(L"Connect Failed Error Code : %d, Desc : %s", errorCode, SystemUtils::WSAGetLastErrorMsg(errorCode).c_str());
}