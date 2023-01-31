#pragma once
#include "DBConnectionPool.h"
#include "DBBind.h"

class DatabaseManager
{
public:
	struct Config
	{
		wstring connstr;
		int32 connCount;
	};

	bool Initialize(const Config& config);

	DBConnectionPtr GetConnection();

	void Destroy();

private:
	DBConnectionPool pool;
};
