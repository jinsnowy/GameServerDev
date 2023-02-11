#include "pch.h"
#include "DatabaseTest.h"
#include "Engine/GlobalConfig.h"

DatabaseTest::DatabaseTest()
{
}

DatabaseTest::~DatabaseTest()
{
}

void DatabaseTest::SetUp()
{
	DatabaseManager::Config config;
	config.connCount = 1;
	config.connstr = Core::Config::dbsn;
	ASSERT_CRASH(dbManager.Initialize(config));

	dbConn = dbManager.GetConnection();
}

void DatabaseTest::TearDown()
{
	dbConn->release();
	dbManager.Destroy();
}