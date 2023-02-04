#include "pch.h"
#include "AccountEntity.h"
#include "Engine/Database/DBUtils.h"

AccountEntity::AccountEntity(wstring username, wstring password)
	:
	_username(username),
	_password(password)
{
}

CREATE_API(AccountEntity)
{
	DBStatement<2, 1> stmt(db_conn, L"usp_CreateAccount");

	stmt.BindParam(0, _username.c_str());
	stmt.BindParam(1, _password.c_str());

	int id = 0;
	stmt.BindCol(0, id);

	bool result = stmt.Execute();
	if (result &= stmt.Fetch(); result == true)
	{
		_id = id;
	}

	return result;
}

REMOVE_API(AccountEntity)
{
	int id = _id.load();

	DBStatement<1, 0> stmt(db_conn, L"usp_DeleteAccount");
	stmt.BindParam(0, id);

	return stmt.Execute();
}

UPDATE_API(AccountEntity)
{

	return true;
}

SELECT_API(AccountEntity)
{
	DBStatement<1, 2> stmt(db_conn, L"usp_SelectAccount");
	stmt.BindParam(0, id);

	wchar_t username_buffer[512];
	wchar_t password_buffer[512];

	stmt.BindCol(0, username_buffer);
	stmt.BindCol(1, password_buffer);

	if (stmt.Execute() && stmt.Fetch()) {
		auto entity = make_shared<AccountEntity>(username_buffer, password_buffer);
		entity->_id = id;
		return entity;
	}

	return nullptr;
}

SELECT_ALL_API(AccountEntity)
{
	DBStatement<0, 2> stmt(db_conn, L"usp_SelectAllAccount");

	wchar_t username_buffer[512];
	wchar_t password_buffer[512];

	stmt.BindCol(0, username_buffer);
	stmt.BindCol(1, password_buffer);

	if (stmt.Execute() == false) {
		return {};
	}

	std::vector<std::shared_ptr<AccountEntity>> entities;
	while (stmt.Fetch()) {
		auto entity = make_shared<AccountEntity>(username_buffer, password_buffer);
		entities.push_back(entity);
	}

	return entities;
}