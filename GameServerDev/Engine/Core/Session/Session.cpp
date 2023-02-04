#include "pch.h"
#include "Session.h"
#include "SessionManager.h"

#include "Core/Buffer/BufferSegment.h"
#include "Core/Network/Object/TcpNetwork.h"

Session::Session()
	:
	_sessionId(INVALID_SESSION_VALUE)
{
}

Session::~Session()
{
	LOG_INFO(L"~Session()");
}

void Session::SendAsync(const BufferSegment& segment)
{
	if (IsConnected() == false || segment.len == 0)
		return;

	_network->SendAsync(segment);
}

void Session::AttachNetwork(shared_ptr<TcpNetwork> network)
{
	if (_network != nullptr && _network->IsConnected())
	{
		_network->CloseBy(L"attach new network");
		_network = nullptr;
	}

	_network = network;

	if (_network && _network->IsConnected())
	{
		OnConnected();
	}
}

void Session::DetachNetwork()
{
	if (_network)
	{
		OnDisconnected();
	}

	_network = nullptr;
}

bool Session::IsConnected()
{
	return _network != nullptr && _network->IsConnected();
}

void Session::Disconnect()
{
	if (_network == nullptr || _network->IsConnected() == false)
		return;

	_network->DisconnectAsync();

	int count = 0;
	while (IsConnected() && ++count < 10)
	{
		std::this_thread::sleep_for(100ms);
	}
}

void Session::DisconnectAsync()
{
	if (_network == nullptr || _network->IsConnected() == false)
		return;

	_network->DisconnectAsync();
}

void Session::OnConnected()
{
	static atomic<SessionID> sessionIDGen = 1;

	SetSessionId(sessionIDGen.fetch_add(1));

	LOG_INFO(L"sessionId %lld connected to %s", GetSessionId(), GetEndPointDesc().c_str());
}

void Session::OnDisconnected()
{
	LOG_INFO(L"disconnected from %s", GetEndPointDesc().c_str());
}

EndPoint Session::GetEndPoint()
{
	return _network != nullptr ? _network->GetEndPoint() : EndPoint();
}
