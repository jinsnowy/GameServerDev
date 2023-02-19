#include "pch.h"
#include "SessionManager.h"

namespace Core {
	namespace Network {
		namespace Session {
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
				_sessionContainer.emplace_back(sessionPtr);
			}

			void SessionManager::RemoveSession(SessionPtrCRef sessionPtr)
			{
				_sessionContainer.erase(std::find(_sessionContainer.begin(), _sessionContainer.end(), sessionPtr));
			}

			vector<shared_ptr<SessionBase>> SessionManager::GetSessions()
			{
				return _sessionContainer;
			}

		}
	}
}