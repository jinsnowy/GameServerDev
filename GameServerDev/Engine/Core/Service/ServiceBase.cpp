#include "pch.h"
#include "ServiceBase.h"

#include "Core/Network/Object/TcpNetwork.h"
#include "Core/Network/IO/IoContext.h"
#include "Core/Task/TaskScheduler.h"
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

IoContext& ServiceBase::GetIoContext()
{
	return GetContext().ioContext;
}

void ServiceBase::Initialize()
{
	_started = false;
	_initCount.store(0);
	_threadContexts.resize(Core::Config::thread_count, nullptr);

	std::vector<std::unique_ptr<std::thread>> threads;
	for (int i = 0; i < Core::Config::thread_count; ++i)
	{
		threads.emplace_back(std::make_unique<std::thread>([this, idx = i]()
			{
				ThreadContext& context = GetContext();

				{
					std::unique_lock<std::mutex> lk(g_process_mtx);

					_threadContexts[idx] = &context;
				}

				ProcessCore(context);
			}));
	}

	bool init = false;
	while (init == false) {

		init = true;
		for (auto& threadContext : _threadContexts)
		{
			std::unique_lock<std::mutex> lk(g_process_mtx);

			if (threadContext == nullptr)
			{
				init = false;
				break;
			}
		}

		Sleep(100);
	}

	try
	{
		for (size_t idx = 0; idx < _threadContexts.size(); ++idx)
		{
			_threadContexts[idx]->worker = std::move(threads[idx]);
		}
	}
	catch (std::exception e) {
		LOG_ERROR(L"init failed : %s", e.what());
		throw e;
	}
}

void ServiceBase::Start()
{
	_started = true;
	_signal.notify_all();

	while (_initCount.load() != _threadContexts.size()) {
		_signal.notify_all();
		Sleep(10);
	}
}

void ServiceBase::ProcessCore(ThreadContext& context)
{
	std::unique_lock lk(g_process_mtx);

	_signal.wait(lk, [this]() { return _started; });

	lk.unlock();

	_initCount.fetch_add(1);

	IoContext* ioContext = &context.ioContext;

	int timeSliceMs = 128;

	while (true)
	{
		ioContext->Dispatch(16);

		taskScheduler->Poll(timeSliceMs);
	}
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

ThreadContext::ThreadContext()
{
}

ThreadContext::~ThreadContext()
{
	Destroy();
}

void ThreadContext::Destroy()
{
	ioContext.Dispose();
	dbConn.reset();

	if (worker->joinable())
	{
		worker->join();
	}
}