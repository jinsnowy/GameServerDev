#pragma once
#include "Singleton.h"
#include "Session.h"

class SessionManager : public ISingleton<SessionManager>
{
public:
	SessionManager();
	~SessionManager();

	void AddSession(SessionPtrCRef sessionPtr);

	void RemoveSession(SessionPtrCRef sessionPtr);

	vector<shared_ptr<Session>> GetSessions();

private:
	StdMutex _sync;
	std::map<SessionID, shared_ptr<Session>> _sessionContainer;
};
