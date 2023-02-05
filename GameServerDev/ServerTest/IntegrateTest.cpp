#include "pch.h"
#include "IntegrateTest.h"

IntegrateTest::IntegrateTest()
{
}

IntegrateTest::~IntegrateTest()
{
}

void IntegrateTest::SetUp()
{
	Core::Initialize();

	_serverMock.Initialize();
	_clientMock.Initialize();

	_serverMock.SetClient(_clientMock.GetNetworkMock());
	_clientMock.SetServer(_serverMock.GetNetworkMock());

	Config::dbsn = g_DBConnStr;
	Config::thread_count = 1;

}

void IntegrateTest::TearDown()
{
	dbManager.Destroy();
}

DBConnectionSourcePtr IntegrateTest::GetDBConnection()
{
	return dbManager.GetConnection();
}
