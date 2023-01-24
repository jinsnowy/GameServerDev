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
	_sessionContainer.emplace(sessionPtr->GetSessionId(), sessionPtr);
}

void SessionManager::RemoveSession(SessionPtrCRef sessionPtr)
{
	WRITE_LOCK(_sync);
	_sessionContainer.erase(sessionPtr->GetSessionId());
}

vector<shared_ptr<Session>> SessionManager::GetSessions()
{
	vector<shared_ptr<Session>> sessions;

	{
		WRITE_LOCK(_sync);

		for (auto& pair : _sessionContainer)
		{
			sessions.push_back(pair.second);
		}
	}

	return sessions;
}
