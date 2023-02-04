#pragma once
#include "DBConnectionPool.h"

class DBConnectionSource;
class DatabaseManager
{
public:
	struct Config
	{
		wstring connstr;
		int32 connCount;
	};

	bool Initialize(const Config& config);

	std::shared_ptr<DBConnectionSource> GetConnection();

	void Destroy();

private:
	DBConnectionPool pool;
};
