#pragma once

#include "Engine/Core/Session/SessionManager.h"

class SessionManagerMock : public SessionManager
{
public:
	SessionManagerMock(SessionFactory sessionFactory);
};

