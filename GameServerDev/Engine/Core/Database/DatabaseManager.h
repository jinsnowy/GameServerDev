#pragma once
#include "DBConnectionPool.h"

class DBConnectionSource;
class DatabaseManager : public ISingleton<DatabaseManager>
{
public:
	DatabaseManager();

	void Initialize();

	DBConnection* GetConnection();

	void Destroy();

	bool IsInitialized();

private:
	bool _initialized;
	DBConnectionPool pool;
};
