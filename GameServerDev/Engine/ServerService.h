#pragma once
#include "ServiceBase.h"
#include "ServerSession.h"

struct ServerServiceParam
{
	uint16 port;
	int backLog;

	ServerServiceParam(uint16 _port, int _backLog)
		:
		port(_port),
		backLog(_backLog)
	{}
};

class LoginSession;
class ServerService : public ServiceBase
{
private:
	uint16 _port;
	int _backLog;
	ServerSessionFactory _sessionFactory;

public:
	ServerService(SessionManager& sessionManager, const ServerServiceParam& param);

	virtual void Start() override;
};