#pragma once
#include <sql.h>
#include <sqlext.h>

enum
{
	WVARCHAR_MAX = 4000,
	BINARY_MAX = 8000
};

class DBConnection
{
public:
	DBConnection();
	~DBConnection();

	bool  Connect(SQLHDBC henv, LPCWSTR connectionString);
	void  Clear();

	bool  Execute(LPCWSTR query, wstring& errorMessage);
	bool  Fetch();
	int32 GetRowCount();
	void  Unbind();

	void BeginTransaction();
	void Commit();
	void Rollback();

public:
	bool BindParam(int32 paramIndex, bool* value, SQLLEN* index);
	bool BindParam(int32 paramIndex, float* value, SQLLEN* index);
	bool BindParam(int32 paramIndex, double* value, SQLLEN* index);
	bool BindParam(int32 paramIndex, int8* value, SQLLEN* index);
	bool BindParam(int32 paramIndex, int16* value, SQLLEN* index);
	bool BindParam(int32 paramIndex, int32* value, SQLLEN* index);
	bool BindParam(int32 paramIndex, int64* value, SQLLEN* index);
	bool BindParam(int32 paramIndex, TIMESTAMP_STRUCT* value, SQLLEN* index);
	bool BindParam(int32 paramIndex, LPCWSTR str, SQLLEN* index);
	bool BindParam(int32 paramIndex, BYTE* bin, int32 size, SQLLEN* index);

	bool BindCol(int32 columnIndex, bool* value, SQLLEN* index);
	bool BindCol(int32 columnIndex, float* value, SQLLEN* index);
	bool BindCol(int32 columnIndex, double* value, SQLLEN* index);
	bool BindCol(int32 columnIndex, int8* value, SQLLEN* index);
	bool BindCol(int32 columnIndex, int16* value, SQLLEN* index);
	bool BindCol(int32 columnIndex, int32* value, SQLLEN* index);
	bool BindCol(int32 columnIndex, int64* value, SQLLEN* index);
	bool BindCol(int32 columnIndex, TIMESTAMP_STRUCT* value, SQLLEN* index);
	bool BindCol(int32 columnIndex, LPCWSTR str, int32 size, SQLLEN* index);
	bool BindCol(int32 columnIndex, BYTE* bin, int32 size, SQLLEN* index);

private:
	bool  BindParam(SQLUSMALLINT paramIndex, SQLSMALLINT cType,  SQLSMALLINT sqlType, SQLULEN len, SQLPOINTER ptr, SQLLEN* index);
	bool  BindCol(SQLUSMALLINT columnIndex, SQLSMALLINT cType, SQLULEN len ,SQLPOINTER value, SQLLEN* index);
	wstring  GetErrorMessage(SQLRETURN ret);

private:
	SQLHDBC _connection = SQL_NULL_HANDLE;
	SQLHSTMT _statement = SQL_NULL_HANDLE;
};

class DBTransaction;
class DBConnectionPool;
class DBConnectionPtr
{
	struct Impl
	{
		DBConnectionPool* pool;
		DBConnection* conn;

		Impl(DBConnectionPool* poolIn, DBConnection* connIn);
		~Impl();
	};
private:
	std::shared_ptr<Impl> impl;

public:
	DBConnectionPtr();
	DBConnectionPtr(DBConnectionPool* poolIn, DBConnection* connIn);
	~DBConnectionPtr();

	DBTransaction StartTransaction();

	DBConnection* operator->() {
		return impl->conn;
	}

	void Clear();
};

class DBTransaction
{
private:
	atomic<bool> committed;
	atomic<bool> rollbacked;
	DBConnectionPtr connPtr;

public:
	DBTransaction(DBConnectionPtr connPtrIn);
	~DBTransaction();

	void Commit();
	void Rollback();
};