#pragma once

#include "Engine/Core/Service/ServiceBase.h"
#include "Engine/Core/Session/SessionManager.h"

class ServiceMock : public ServiceBase
{
public:
	ServiceMock(SessionManager& sessionManager);
};

