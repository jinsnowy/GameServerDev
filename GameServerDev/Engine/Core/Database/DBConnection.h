#pragma once
#include <sql.h>
#include <sqlext.h>

class DBStatement;
class DBTransaction;
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

	bool  Execute(LPCWSTR query);
	bool  Fetch(bool& eof);
	int32 GetRowCount();
	void  Unbind();

	void BeginTransaction();
	void Commit();
	void Rollback();

	std::unique_ptr<DBStatement> CreateStatement();
	std::unique_ptr<DBTransaction> StartTransaction();
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
	bool BindParam(int32 paramIndex, const std::wstring& str, SQLLEN* index);
	bool BindParam(int32 paramIndex, BYTE* bin, int32 size, SQLLEN* index);

	bool BindResult(int32 columnIndex, bool* value, SQLLEN* index);
	bool BindResult(int32 columnIndex, float* value, SQLLEN* index);
	bool BindResult(int32 columnIndex, double* value, SQLLEN* index);
	bool BindResult(int32 columnIndex, int8* value, SQLLEN* index);
	bool BindResult(int32 columnIndex, int16* value, SQLLEN* index);
	bool BindResult(int32 columnIndex, int32* value, SQLLEN* index);
	bool BindResult(int32 columnIndex, int64* value, SQLLEN* index);
	bool BindResult(int32 columnIndex, TIMESTAMP_STRUCT* value, SQLLEN* index);
	bool BindResult(int32 columnIndex, LPCWSTR str, int32 size, SQLLEN* index);
	bool BindResult(int32 columnIndex, BYTE* bin, int32 size, SQLLEN* index);

	bool BindOutputParam(int32 paramIndex, int32* value);
	
	SQLHDBC StatementHandle() { return _statement; }

	wstring  last_error_message() { return _last_error_message; }
private:
	bool  BindParam(SQLUSMALLINT paramIndex, SQLSMALLINT cType,  SQLSMALLINT sqlType, SQLULEN len, SQLPOINTER ptr, SQLLEN* index);
	bool  BindResult(SQLUSMALLINT columnIndex, SQLSMALLINT cType, SQLULEN len ,SQLPOINTER value, SQLLEN* index);
	
private:
	void HandleError(SQLRETURN error);

	wstring _last_error_message;
	SQLHDBC _connection = SQL_NULL_HANDLE;
	SQLHSTMT _statement = SQL_NULL_HANDLE;
};