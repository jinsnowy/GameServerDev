#pragma once

#include "Engine/DBUtils.h"

class DatabaseTest : public ::testing::Test
{
public:
	DatabaseTest();
	~DatabaseTest();

	virtual void SetUp() override;

	virtual void TearDown() override;

protected:
	DBConnectionSourcePtr dbConn;
	DatabaseManager dbManager;
};

