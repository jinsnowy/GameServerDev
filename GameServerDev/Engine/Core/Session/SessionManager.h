#pragma once

#include "Session.h"

class SessionManager
{
	friend class ServiceBase;
private:
	SessionFactory _sessionFactory;

public:
	SessionManager(SessionFactory sessionFactory);
	
	virtual ~SessionManager();

	SessionPtr NewSession();

	vector<shared_ptr<Session>> GetSessions();

	void AddSession(SessionPtrCRef sessionPtr);

	void RemoveSession(SessionPtrCRef sessionPtr);

private:
	StdMutex _sync;
	std::vector<shared_ptr<Session>> _sessionContainer;
};
