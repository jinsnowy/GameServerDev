#include "pch.h"
#include "DBConnectionPool.h"
#include "DBConnection.h"

DBConnectionPool::DBConnectionPool()
	:
	_environment(SQL_NULL_HANDLE)
{
}

DBConnectionPool::~DBConnectionPool()
{
	Clear();
}

bool DBConnectionPool::Connect(int32 connectionCount, LPCWSTR connectionString)
{
	_connStr = connectionString;

	if (::SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &_environment) != SQL_SUCCESS)
		return false;

	if (::SQLSetEnvAttr(_environment, SQL_ATTR_ODBC_VERSION, reinterpret_cast<SQLPOINTER>(SQL_OV_ODBC3), 0) != SQL_SUCCESS)
		return false;

	for (int32 i = 0; i < connectionCount; ++i)
	{
		DBConnection* conn = new DBConnection();
		if (conn->Connect(_environment, connectionString) == false)
			return false;
		
		_connections.push_back(conn);
	}

	return true;
}

void DBConnectionPool::Clear()
{
	if (_environment != SQL_NULL_HANDLE)
	{
		::SQLFreeHandle(SQL_HANDLE_ENV, _environment);
		_environment = SQL_NULL_HANDLE;
	}

	int connectionCount = (int)_connections.size();
	for (int i = 0; i < connectionCount; ++i)
	{
		delete _connections[i];
	}

	_connections.clear();
}

DBConnection* DBConnectionPool::GetConnection()
{
	auto conn = _connections.back();
	_connections.pop_back();

	return conn;
}

void DBConnectionPool::Push(DBConnection* connection)
{
	_connections.push_back(connection);
}

DBConnection* DBConnectionPool::AddConnection()
{
	DBConnection* conn = new DBConnection();
	if (conn->Connect(_environment, _connStr.c_str()) == false)
		return nullptr;

	return conn;
}
