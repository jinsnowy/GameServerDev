#include "pch.h"
#include "ServiceBase.h"

#include "Core/Actor/Actor.h"
#include "Core/Context/IoContext.h"
#include "Core/Context/ExecutionContext.h"
#include "Core/Context/ThreadContext.h"
#include "Core/Network/Object/TcpNetwork.h"
#include "Core/Session/SessionManager.h"

std::mutex ServiceBase::g_process_mtx = {};

ServiceBase::ServiceBase(SessionFactory sessionFactory, NetworkFactory networkFactory)
	:
	_sessionManager(sessionFactory),
	_networkFactory(networkFactory),
	_started(false)
{
}

ServiceBase::~ServiceBase()
{
	Stop();
}

ThreadContext& ServiceBase::GetContext()
{
	thread_local ThreadContext context;
	return context;
}

SessionManager& ServiceBase::GetSessionManager()
{
	return _sessionManager;
}

void ServiceBase::Initialize()
{
	_started = false;
	_workers.clear();
	_threadContexts.clear();

	try {
		CreateWorkerThreads();
	}
	catch (const std::exception& e) {
		LOG_ERROR(L"init failed : %s", e.what());
		throw e;
	}
}

void ServiceBase::Start()
{
	_started = true;
	_initCount.store(0);
	_signal.notify_all();

	while (_initCount.load() != _workers.size()) {
		_signal.notify_all();
		Sleep(10);
	}
}

void ServiceBase::ProcessCore()
{
	{
		std::unique_lock lk(g_process_mtx);

		_signal.wait(lk, [this]() { return _started; });
	}

	_initCount.fetch_add(1);

	GetContext().Process();
}

void ServiceBase::Run(std::function<void()> func)
{
	func();
}

void ServiceBase::RunIdle()
{
	while (true)
	{
		std::this_thread::sleep_for(5s);
	}
}

void ServiceBase::Stop()
{
	for (size_t idx = 0; idx < _threadContexts.size(); ++idx)
	{
		_threadContexts[idx]->Destroy();
	}

	_threadContexts.clear();
	
	for (auto& worker : _workers) {
		if (worker.joinable()) {
			worker.join();
		}
	}
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

void ServiceBase::CreateWorkerThreads()
{
	for (int i = 0; i < Core::Config::thread_count; ++i) {
		_workers.emplace_back([this]()
		{
			{
				std::unique_lock<std::mutex> lk(g_process_mtx);

				_threadContexts.push_back(&GetContext());

				GetContext().GetExecutionContext()->Register();
			}

			ProcessCore();
		});
	}
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