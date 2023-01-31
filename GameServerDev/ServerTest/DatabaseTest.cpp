#include "pch.h"
#include "DatabaseTest.h"
#include "GlobalConfig.h"

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
	config.connstr = L"Driver={ODBC Driver 17 for SQL Server};Server=DESKTOP-5DKI3L6;Trusted_Connection=Yes;Database=GameDB;";
	ASSERT_CRASH(dbManager.Initialize(config));

	dbConn = dbManager.GetConnection();
}

void DatabaseTest::TearDown()
{
	dbConn.Clear();
	dbManager.Destroy();
}