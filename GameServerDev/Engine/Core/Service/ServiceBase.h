#pragma once

#include "../Session/Session.h"
#include "../Session/SessionManager.h"
#include "../Memory/MemoryPool.h"
#include "../Repository/Repository.h"
#include "../Context/ThreadContext.h"
#include "../Actor/Actor.h"

class IoContext;
class ThreadContext;
class ServiceBase : public Actor
{
protected:
	static std::mutex g_process_mtx;

public:
	ServiceBase(SessionFactory sessionFactory, NetworkFactory networkFactory);

	~ServiceBase();

	virtual void Start();

	virtual void Initialize();

	virtual void Stop();

	void Run(function<void()> func);

	void RunIdle();

	ThreadContext& GetContext();
	SessionManager& GetSessionManager();

	virtual void OnConnectedNetwork(NetworkPtr network);
	virtual void OnDisconnectedNetwork(NetworkPtr network);
	virtual void OnAuthNetwork(NetworkPtr network);

protected:
	SessionManager _sessionManager;
	NetworkFactory _networkFactory;

protected:
	bool				   _started;
	atomic<int>			   _initCount;
	std::condition_variable _signal;
	vector<std::thread>    _workers;
	vector<ThreadContext*> _threadContexts;

	void CreateWorkerThreads();
	void ProcessCore();

private:
	StdMutex _mtx;
	unordered_map<wstring, NetworkPtr> _acceptNetworks;

	void AddNetwork(NetworkPtr network);
	void RemoveNetwork(NetworkPtr network);

	vector<NetworkPtr> GetNetworks();

protected:
	std::map<wstring, function<unique_ptr<Repository>()>> _repository_factories;

public:
	template<typename T>
	requires std::is_base_of_v<Repository, T>
	void RegisterRepository() 
	{
		const wstring& tag = Reflection::GetTypeInfo<T>().name_str_w;
		if (_repository_factories.find(tag) == _repository_factories.end()) {
			_repository_factories[tag] = []() { return unique_ptr<Repository>(new T()); };
		}
	}
};