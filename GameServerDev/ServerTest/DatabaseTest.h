#pragma once
#include "DatabaseManager.h"

class DatabaseTest : public ::testing::Test
{
public:
	DatabaseTest();
	~DatabaseTest();

	virtual void SetUp() override;

	virtual void TearDown() override;

protected:
	DBConnectionPtr dbConn;
	DatabaseManager dbManager;
};

