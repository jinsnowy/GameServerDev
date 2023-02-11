#include "pch.h"
#include "ServerServiceMock.h"

ServerServiceMock::ServerServiceMock(SessionFactory sessionFactory, NetworkFactory networkFactory)
	:
	ServerService(sessionFactory, networkFactory)
{
}
