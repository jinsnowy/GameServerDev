#pragma once

#include "ServerMock.h"
#include "ClientMock.h"
#include "Engine/Database/DatabaseManager.h"

class IntegrateTest : public ::testing::Test
{
public:
	IntegrateTest();
	~IntegrateTest();

	virtual void SetUp() override;

	virtual void TearDown() override;

protected:
	DBConnectionSourcePtr GetDBConnection();

private:
	ServerMock _serverMock;
	ClientMock _clientMock;
};

