#pragma once

#include "DBConnection.h"

class DBConnectionSource;
class DBStatement
{
public:
	DBStatement(DBConnectionSourcePtr dbConnSource);

	void Execute(const wchar_t* query);

	bool Success() { return _success && _result == 0; }

	wstring error_message();

	bool FetchResult();

	bool FetchEnd();

public:
	template<typename T>
	requires std::is_integral_v<T>
	void BindParam(T& value)
	{
		++_ParamCount;
		_dbConnection->BindParam(_ParamCount, &value, &_OutLenForParam[_ParamCount - 1]);
	}

	void BindParam(LPCWSTR str)
	{
		++_ParamCount;
		_dbConnection->BindParam(_ParamCount, str, &_OutLenForParam[_ParamCount - 1]);
	}

	void BindParam(const std::wstring& str) 
	{
		++_ParamCount;
		_dbConnection->BindParam(_ParamCount, str, &_OutLenForParam[_ParamCount - 1]);
	}

	template<typename T, int32 NArr>
	void BindParam(T(&value)[NArr])
	{
		++_ParamCount;
		_dbConnection->BindParam(_ParamCount, (BYTE*)value, size32(T) * NArr, &_OutLenForParam[_ParamCount - 1]);
	}

	template<typename T>
	void BindResult(T& value)
	{
		++_ColCount;
		_dbConnection->BindResult(_ColCount, &value, &_OutLenForCol[_ColCount - 1]);
	}

	template<typename T, int32 NArr>
	void BindResult(wchar_t (&buffer)[NArr])
	{
		++_ColCount;
		_dbConnection->BindResult(_ColCount, buffer, sizeof(buffer), &_OutLenForCol[_ColCount - 1]);
	}

	template<typename T, int32 NArr>
	void BindResult(T(&value)[NArr])
	{
		++_ColCount;
		_dbConnection->BindResult(_ColCount, (BYTE*)value, size32(T) * NArr, &_OutLenForCol[_ColCount - 1]);
	}

	SQLHDBC GetHandle();

protected:
	DBConnectionSourcePtr _connSource;
	DBConnection* _dbConnection;

	bool		   _eof;
	bool		   _success;
	int32		   _result;
	wstring		   _bind_str;

	int32		   _ParamCount;
	int32		   _ColCount;
	SQLLEN		   _OutLenForParam[10];
	SQLLEN         _OutLenForCol[10];

private:
	void BindOutputResult()
	{
		++_ParamCount;
		_dbConnection->BindOutputParam(_ParamCount, &_result);
	}
};