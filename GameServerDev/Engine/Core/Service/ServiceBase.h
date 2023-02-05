#pragma once

#include "../Session/Session.h"
#include "../Session/SessionManager.h"
#include "../Network/IO/IoContext.h"
#include "../Memory/MemoryPool.h"
#include "../Repository/Repository.h"

#include "../../Database/DatabaseManager.h"
#include "../../Database/DBConnectionSource.h"

class IoContext;
struct ThreadContext
{
	unique_ptr<std::thread> worker;
	IoContext ioContext;
	DBConnectionSourcePtr dbConn;
	std::unordered_map<std::wstring, std::unique_ptr<Repository>> repositories;

	ThreadContext();
	~ThreadContext();

	void Destroy();

	template<typename T>
	requires std::is_base_of_v<Repository, T>
	T* GetRepository()
	{
		const wstring& tag = Reflection::GetTypeInfo<T>().name_str_w;
		return static_cast<T*>(repositories[tag].get());
	}

	DBConnectionSourcePtr& GetDBConn() 
	{
		return dbConn;
	}

	NO_COPY_AND_ASSIGN(ThreadContext);
};

class ServiceBase
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
	IoContext& GetIoContext();

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
	vector<ThreadContext*> _threadContexts;

	void ProcessCore(ThreadContext& context);

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