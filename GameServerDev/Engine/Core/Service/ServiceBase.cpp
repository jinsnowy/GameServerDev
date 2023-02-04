#include "pch.h"
#include "ServiceBase.h"

#include "Core/Network/Object/TcpNetwork.h"
#include "Core/Network/IO/IoContext.h"
#include "Core/Task/TaskScheduler.h"
#include "Core/Session/SessionManager.h"

ServiceBase::ServiceBase(SessionManager& sessionManager, int threadWorkerNum)
	:
	_sessionManager(sessionManager),
	_threadNum(threadWorkerNum)
{
}

ServiceBase::~ServiceBase()
{
	Stop();
}

void ServiceBase::Start()
{
	for (int i = 0; i < _threadNum; ++i)
	{
		_threadWorkers.emplace_back([this]()
		{ 
				ProcessCore();
		});
	}
}

void ServiceBase::Run(std::function<void()> func)
{
	func();
}

void ServiceBase::OnConnectedNetwork(NetworkPtr network)
{
	AddNetwork(network);
}

void ServiceBase::OnDisconnectedNetwork(NetworkPtr network)
{
	RemoveNetwork(network);

	SessionPtr session = network->GetSession();
	if (session) 
	{
		_sessionManager.RemoveSession(session);
	}
}

void ServiceBase::OnAuthNetwork(NetworkPtr network)
{
	RemoveNetwork(network);

	static atomic<SessionID> sessionIdGen;

	SessionID sessionId = sessionIdGen.fetch_add(1);

	auto session = _sessionManager.NewSession();

	session->SetSessionId(sessionId);

	_sessionManager.AddSession(session);

	network->AttachSession(session);
}

void ServiceBase::AddNetwork(NetworkPtr network)
{
	WRITE_LOCK(_mtx);

	wstring netAddress = network->GetEndPoint().ToString();

	_acceptNetworks.emplace(netAddress, network);
}

void ServiceBase::RemoveNetwork(NetworkPtr network)
{
	WRITE_LOCK(_mtx);

	wstring netAddress = network->GetEndPoint().ToString();

	_acceptNetworks.erase(netAddress);
}

vector<NetworkPtr> ServiceBase::GetNetworks()
{
	WRITE_LOCK(_mtx);

	vector<NetworkPtr> networks;
	for (auto& pair : _acceptNetworks) {
		networks.push_back(pair.second);
	}

	return networks;
}

void ServiceBase::Stop()
{
	_ioContext.Dispose();

	for (auto& worker : _threadWorkers)
	{
		if (worker.joinable())
		{
			worker.join();
		}
	}
}

void ServiceBase::ProcessCore()
{
	TaskScheduler* taskScheduler = TaskScheduler::GetInstance();
	
	int timeSliceMs = 128;

	while (true)
	{
		_ioContext.Dispatch(16);

		taskScheduler->Poll(timeSliceMs);
	}
}
