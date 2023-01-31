#pragma once

#include <sql.h>
#include <sqlext.h>

class DBConnectionSource;
class DBConnection;
class DBConnectionPool
{
	friend class DBConnectionSource;
public: 
	DBConnectionPool();
	~DBConnectionPool();

	bool Connect(int32 connectionCount, LPCWSTR connectionString);
	void Clear();
	std::shared_ptr<DBConnectionSource>  GetConnection();

private:
	wstring _connStr;
	StdMutex _mtx;
	SQLHENV  _environment;
	vector<DBConnection*> _connections;

private:
	void Push(DBConnection* connection);

	DBConnection* AddConnection();
};