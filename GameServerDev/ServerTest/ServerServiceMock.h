#pragma once

#include "Engine/Core/Service/ServerService.h"

class ServerServiceMock : public ServerService
{
public:
	ServerServiceMock(SessionFactory sessionFactory, NetworkFactory networkFactory);
};

