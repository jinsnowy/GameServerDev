#pragma once

#include "../Session/Session.h"

class ClientService;
class ClientServiceBuilder : public Builder<ClientServiceBuilder>
{
public:
	EndPoint _endPoint;
	int _clientNum;
	SessionFactory _sessionFactory;
	NetworkFactory _networkFactory;

public:
	ClientServiceBuilder();

	shared_ptr<ClientService> Build();

	auto& EndPoint(const EndPoint& endPoint)
	{
		_endPoint = endPoint;
		return self();
	}

	auto& ClientNum(int num) {
		_clientNum = num;
		return self();
	}

	auto& Sessions(SessionFactory sessionFactory) {
		_sessionFactory = sessionFactory;
		return self();
	}

	auto Networks(NetworkFactory networkFactory) {
		_networkFactory = networkFactory;
		return self();
	}
};

