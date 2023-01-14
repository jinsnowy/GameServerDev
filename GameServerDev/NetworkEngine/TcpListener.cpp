#include "pch.h"
#include "TcpListener.h"
#include "TcpNetwork.h"

TcpListener::TcpListener(ServiceBase& serviceBase, ListenerConfig config)
	:
	_serviceBase(serviceBase),
	_finished(false),
	_config(config),
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

	if (!_listenerNetwork.Bind(_config.bindPort)) {
		return false;
	}

	if (!_listenerNetwork.Listen(_config.backLog)) {
		return false;
	}

	for (int32 i = 0; i < _config.acceptCount; ++i) {
		RegisterAccpet();
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

	if (!_config.onAccept(network))
	{
		return false;
	}

	network->Start();

	return true;
}

void TcpListener::RegisterAccpet()
{
	NetworkPtr network = _config.networkFactory(_serviceBase);
	LPVOID bufferPtr = network->GetRecvBuffer().GetBufferPtr();

	if (!_listenerNetwork.AcceptAsync(shared_from_this(), network, bufferPtr))
	{
		LOG_ERROR(L"accept error : %s", get_last_err_msg());
	}
}
