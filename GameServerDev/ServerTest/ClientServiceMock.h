#pragma once

#include "Engine/Core/Service/ClientService.h"

class ClientServiceMock : public ClientService
{
public:
	ClientServiceMock(SessionFactory sessionFactory, NetworkFactory networkFactory);
};

