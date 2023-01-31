#pragma once

#include "DatabaseManager.h"

class IntegrateTest : public ::testing::Test
{
public:
	IntegrateTest();
	~IntegrateTest();

	virtual void SetUp() override;

	virtual void TearDown() override;

protected:
	DBConnectionPtr GetDBConnection();

private:
	DatabaseManager dbManager;
};

