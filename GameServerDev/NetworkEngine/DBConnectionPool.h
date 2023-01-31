#pragma once

#include "DBConnection.h"

class DBConnectionPool
{
	friend class DBConnectionPtr;
public: 
	DBConnectionPool();
	~DBConnectionPool();

	bool Connect(int32 connectionCount, LPCWSTR connectionString);
	void Clear();
	DBConnectionPtr GetConnection();

private:
	wstring _connStr;
	StdMutex _mtx;
	SQLHENV  _environment = SQL_NULL_HANDLE;
	vector<DBConnection*> _connections;

private:
	void Push(DBConnection* connection);

	DBConnection* AddConnection();
};