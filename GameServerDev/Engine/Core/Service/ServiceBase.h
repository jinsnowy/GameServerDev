#pragma once

#include "../Session/Session.h"
#include "../Network/IO/IoContext.h"

class IoContext;
class SessionManager;
class ServiceBase
{
public:
	ServiceBase(SessionManager& sessionManager, int threadWorkerNum);

	~ServiceBase();

	virtual void Start();

	void Run(function<void()> func);

	IoContext& GetContext() { return _ioContext; }

	virtual void OnConnectedNetwork(NetworkPtr network);
	virtual void OnDisconnectedNetwork(NetworkPtr network);
	virtual void OnAuthNetwork(NetworkPtr network);

protected:
	SessionManager& _sessionManager;

	virtual void Stop();

private:
	IoContext	   _ioContext;
	int			   _threadNum;
	vector<thread> _threadWorkers;

private:
	void ProcessCore();

private:
	StdMutex _mtx;
	unordered_map<wstring, NetworkPtr> _acceptNetworks;

	void AddNetwork(NetworkPtr network);
	void RemoveNetwork(NetworkPtr network);

	vector<NetworkPtr> GetNetworks();
};