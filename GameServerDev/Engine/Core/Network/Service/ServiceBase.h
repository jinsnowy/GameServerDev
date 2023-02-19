#pragma once

#include "../Session/SessionBase.h"
#include "../Session/SessionManager.h"
#include "../../System/Memory/MemoryPool.h"
#include "../../System/Actor/Actor.h"
#include "../../Repository/Repository.h"

namespace Core {
	namespace System {
		class IoContext;
		class ThreadContext;
	}
	namespace Network {
		namespace Service {
			class ServiceBase : public System::Actor::Actor
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

				System::ThreadContext& GetContext();
				Network::Session::SessionManager& GetSessionManager();

				virtual void OnConnectedNetwork(NetworkPtr network);
				virtual void OnDisconnectedNetwork(NetworkPtr network);
				virtual void OnAuthNetwork(NetworkPtr network);

			protected:
				Network::Session::SessionManager _sessionManager;
				NetworkFactory _networkFactory;

			protected:
				bool				   _started;
				atomic<int>			   _initCount;
				std::condition_variable _signal;
				vector<std::thread>    _workers;
				vector<System::ThreadContext*> _threadContexts;

				void CreateWorkerThreads();
				void ProcessCore();

			private:
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
		}
	}
}