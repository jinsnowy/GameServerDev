#include "pch.h"
#include "TcpListener.h"
#include "TcpNetwork.h"
#include "SessionManager.h"

TcpListener::TcpListener(ServiceBase& serviceBase)
	:
	_serviceBase(serviceBase),
	_finished(false),
	_listenerNetwork(serviceBase)
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

	for (int32 i = 0; i < _acceptCount; ++i) {
		RegisterAccept();
	}

	LOG_INFO(L"listen... %s", _listenerNetwork.GetBindAddress().ToString().c_str());

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

	if (!OnAccept(network))
	{
		return false;
	}

	network->Start();

	return true;
}

void TcpListener::RegisterAccept()
{
	NetworkPtr network = _networkFactory(_serviceBase);
	LPVOID bufferPtr = network->GetRecvBuffer().GetBufferPtr();

	if (!_listenerNetwork.AcceptAsync(shared_from_this(), network, bufferPtr))
	{
		LOG_ERROR(L"accept error : %s", get_last_err_msg());
	}
}

bool TcpListener::OnAccept(const NetworkPtr& network)
{
	auto session = _sessionFactory();
	network->AttachSession(session);

	SessionManager::GetInstance()->AddSession(session);

	return true;
}