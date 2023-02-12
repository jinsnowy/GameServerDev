#pragma once
#include "ServiceBase.h"
#include "../Session/ServerSession.h"

class LoginSession;
class ServerService : public ServiceBase
{
	friend class ServerServiceBuilder;
private:
	uint16 _port;
	int32 _backLog;
	int32 _acceptCount;

public:
	ServerService(SessionFactory sessionFactory, NetworkFactory networkFactory);

	virtual void Initialize();

	virtual void Start() override;
};