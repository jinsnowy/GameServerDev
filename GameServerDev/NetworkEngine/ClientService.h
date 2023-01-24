#pragma once
#include "ServiceBase.h"

struct ClientServiceParam
{
	const char* address;
	uint16 port;
	int clientNum;
	int workerNum;

	ClientServiceParam(int _clientNum, int _workerNum, const char* _address, uint16 _port)
		:
		clientNum(_clientNum), workerNum(_workerNum),
		address(_address), port(_port)
	{}
};

class ClientSession;
class ClientService : public ServiceBase
{
private:
	int _clientNum;
	EndPoint _endPoint;

public:
	ClientService(SessionManager& sessionManager, const ClientServiceParam& param);

	virtual void Start() override;

	void Broadcast(BufferSegment buffer);

	void ForEach(function<void(SessionPtr)> func);
};