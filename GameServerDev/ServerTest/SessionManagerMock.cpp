#include "pch.h"
#include "SessionManagerMock.h"
#include "Engine/Core/Session/Session.h"

SessionManagerMock::SessionManagerMock(SessionFactory sessionFactory)
	:
	SessionManager(sessionFactory)
{
}
