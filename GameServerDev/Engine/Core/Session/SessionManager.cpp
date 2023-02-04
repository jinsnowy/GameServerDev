#include "pch.h"
#include "SessionManager.h"

SessionManager::SessionManager(SessionFactory sessionFactory)
	:
	_sessionFactory(sessionFactory)
{
}

SessionManager::~SessionManager()
{
}

SessionPtr SessionManager::NewSession()
{
	return _sessionFactory();
}

void SessionManager::AddSession(SessionPtrCRef sessionPtr)
{
	WRITE_LOCK(_sync);
	_sessionContainer.emplace_back(sessionPtr);
}

void SessionManager::RemoveSession(SessionPtrCRef sessionPtr)
{
	WRITE_LOCK(_sync);
	_sessionContainer.erase(std::find(_sessionContainer.begin(), _sessionContainer.end(), sessionPtr));
}

vector<shared_ptr<Session>> SessionManager::GetSessions()
{
	WRITE_LOCK(_sync);

	return _sessionContainer;
}
