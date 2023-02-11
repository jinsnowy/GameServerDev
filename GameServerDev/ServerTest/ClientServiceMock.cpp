#include "pch.h"
#include "ClientServiceMock.h"

ClientServiceMock::ClientServiceMock(SessionFactory sessionFactory, NetworkFactory networkFactory)
	:
	ClientService(sessionFactory, networkFactory)
{
}
