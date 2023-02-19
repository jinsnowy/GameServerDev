#pragma once

#include "SessionBase.h"

namespace Core {
	namespace Network {
		namespace Session {
			class SessionManager
			{
				friend class Service::ServiceBase;
			private:
				SessionFactory _sessionFactory;

			public:
				SessionManager(SessionFactory sessionFactory);

				virtual ~SessionManager();

				SessionPtr NewSession();

				vector<shared_ptr<SessionBase>> GetSessions();

				void AddSession(SessionPtrCRef sessionPtr);

				void RemoveSession(SessionPtrCRef sessionPtr);

			private:
				std::vector<shared_ptr<SessionBase>> _sessionContainer;
			};
		}
	}
}