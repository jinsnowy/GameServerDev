#include "pch.h"
#include "DBStatement.h"
#include "DBConnection.h"

DBStatement::DBStatement(DBConnection* db_conn)
	:
	_dbConnection(db_conn),
	_result(0),
	_success(false),
	_eof(false),
	_ParamCount(0),
	_ColCount(0)
{
	SystemUtils::Zero(_OutLenForParam);
	SystemUtils::Zero(_OutLenForCol);

	_dbConnection->Unbind();
	BindOutputResult();
}

void DBStatement::Execute(const wchar_t* query)
{
	wstringstream wss;
	size_t paramCount = _ParamCount - 1;
	for (size_t i = 0; i < paramCount; ++i) {
		wss << "?"; if (i != paramCount - 1) wss << ", ";
	}
	_bind_str = wss.str();
	_eof = false;

	wchar_t buffer[512];
	swprintf_s(buffer, L"exec ? = %s %s", query, _bind_str.c_str());
	_success = _dbConnection->Execute(buffer);
}

bool DBStatement::FetchResult()
{
	return _dbConnection->Fetch(_eof);
}

bool DBStatement::FetchEnd()
{
	return _eof;
}

SQLHDBC DBStatement::GetHandle()
{
	return _dbConnection->StatementHandle();
}

wstring DBStatement::error_message()
{
	return _dbConnection->last_error_message();
}