#pragma once
#include "ServiceBase.h"

class TcpConnector;
class ClientSession;
class ClientService : public ServiceBase
{
	friend class ClientServiceBuilder;
private:
	int _clientNum;
	EndPoint _endPoint;
	vector<shared_ptr<TcpConnector>> _connectors;

public:
	ClientService(SessionFactory sessionFactory, NetworkFactory networkFactory);

	virtual void Initialize();

	virtual void Start() override;

	void Broadcast(BufferSegment buffer);

	void ForEach(function<void(SessionPtr)> func);

	void CreateJobOnActiveContext(std::function<void()> func);
};