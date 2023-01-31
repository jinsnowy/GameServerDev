#include "pch.h"
#include "IntegrateTest.h"
#include "Engine/GlobalConfig.h"

IntegrateTest::IntegrateTest()
{
}

IntegrateTest::~IntegrateTest()
{
}

void IntegrateTest::SetUp()
{
	NetUtils::Initialize();
	MemoryPool::Initialize();

	DatabaseManager::Config config;
	config.connCount = 1;
	config.connstr = L"Driver={ODBC Driver 17 for SQL Server};Server=DESKTOP-5DKI3L6;Trusted_Connection=Yes;Database=GameDB;";
	ASSERT_CRASH(dbManager.Initialize(config));
}

void IntegrateTest::TearDown()
{
	dbManager.Destroy();
}

DBConnectionSourcePtr IntegrateTest::GetDBConnection()
{
	return dbManager.GetConnection();
}
