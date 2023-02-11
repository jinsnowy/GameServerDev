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

	ServerMock& Server() { return _serverMock; }
	ClientMock& Client() { return _clientMock; }

private:
	ServerMock _serverMock;
	ClientMock _clientMock;
};