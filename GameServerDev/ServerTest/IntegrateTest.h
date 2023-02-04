#pragma once

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
	DatabaseManager dbManager;
};

