#pragma once

#include "DBConnectionSource.h"
#include "DBConnection.h"

template<int32 ParamCount, int32 ColumnCount>
class DBStatement
{
public:
	DBStatement(DBConnectionSourcePtr dbConnSource, const wchar_t* proc_query)
		:
		_connSource(dbConnSource),
		_dbConnection(dbConnSource->Get()),
		_query(proc_query)
	{
		ZeroMemory(_paramIndex, sizeof(_paramIndex));
		ZeroMemory(_columnIndex, sizeof(_columnIndex));
		_paramFlag.reset();
		_columnFlag.reset();
		_dbConnection->Unbind();

		wstringstream wss;
		for (int32 i = 0; i < ParamCount; ++i) {
			wss << "?"; if (i != ParamCount - 1) wss << ", ";
		}
		_bind_str = wss.str();
	}

	bool Validate()
	{
		return _paramFlag.all() && _columnFlag.all();
	}

	bool Execute()
	{
		ASSERT_CRASH(Validate());

		wchar_t buffer[512];
		swprintf_s(buffer, L"exec %s %s", _query, _bind_str.c_str());
		return  _dbConnection->Execute(buffer);
	}

	wstring error_message() { return _dbConnection->last_error_message(); }

	bool Fetch()
	{
		return _dbConnection->Fetch();
	}

public:
	template<typename T>
	void BindParam(int32 idx, T& value)
	{
		_dbConnection->BindParam(idx + 1, &value, &_paramIndex[idx]);
		_paramFlag.set(idx);
	}

	void BindParam(int32 idx, LPCWSTR str)
	{
		_dbConnection->BindParam(idx + 1, str, &_paramIndex[idx]);
		_paramFlag.set(idx);
	}

	template<typename T, int32 NArr>
	void BindParam(int32 idx, T(&value)[NArr])
	{
		_dbConnection->BindParam(idx + 1, (BYTE*)value, size32(T) * NArr, &_paramIndex[idx]);
		_paramFlag.set(idx);
	}

	template<typename T>
	void BindCol(int32 idx, T& value)
	{
		_dbConnection->BindCol(idx + 1, &value, &_columnIndex[idx]);
		_columnFlag.set(idx);
	}

	void BindCol(int32 idx, LPCWSTR str)
	{
		_dbConnection->BindCol(idx + 1, &str, &_columnIndex[idx]);
		_columnFlag.set(idx);
	}

	template<typename T, int32 NArr>
	void BindCol(int32 idx, T(&value)[NArr])
	{
		_dbConnection->BindCol(idx + 1, (BYTE*)value, size32(T) * NArr, &_columnIndex[idx]);
		_columnFlag.set(idx);
	}

protected:
	DBConnectionSourcePtr _connSource;
	DBConnection* _dbConnection;

	LPCWSTR		  _query;
	wstring		  _bind_str;
	SQLLEN		  _paramIndex[ParamCount > 0 ? ParamCount : 1];
	SQLLEN		  _columnIndex[ColumnCount > 0 ? ColumnCount : 1];
	bitset<ParamCount>  _paramFlag;
	bitset<ColumnCount> _columnFlag;
};