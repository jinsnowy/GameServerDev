#include "pch.h"
#include "AccountEntity.h"
#include "DatabaseManager.h"

AccountEntity::AccountEntity(wstring username, wstring password)
	:
	_username(username),
	_password(password)
{
}

bool AccountEntity::Create(DBConnectionPtr& db_conn)
{
	DBBind<2, 1> binder(db_conn, L"usp_CreateAccount");

	binder.BindParam(0, _username.c_str());
	binder.BindParam(1, _password.c_str());

	int id = 0;
	binder.BindCol(0, id);

	bool result = binder.Execute();
	if (result &= binder.Fetch(); result == true)
	{
		_id = id;
	}

	return result;
}

bool AccountEntity::Remove(DBConnectionPtr& db_conn)
{
	int id = _id.load();

	DBBind<1, 0> binder(db_conn, L"usp_DeleteAccount");
	binder.BindParam(0, id);

	return binder.Execute();
}

SELECT_API(AccountEntity)
{
	DBBind<1, 2> binder(db_conn, L"usp_SelectAccount");
	binder.BindParam(0, id);

	wchar_t username_buffer[512];
	wchar_t password_buffer[512];

	binder.BindCol(0, username_buffer);
	binder.BindCol(1, password_buffer);

	if (binder.Execute() && binder.Fetch()) {
		auto entity = make_shared<AccountEntity>(username_buffer, password_buffer);
		entity->_id = id;
		return entity;
	}

	return nullptr;
}

SELECT_ALL_API(AccountEntity)
{
	DBBind<0, 2> binder(db_conn, L"usp_SelectAllAccount");

	wchar_t username_buffer[512];
	wchar_t password_buffer[512];

	binder.BindCol(0, username_buffer);
	binder.BindCol(1, password_buffer);

	if (binder.Execute() == false) {
		return {};
	}

	std::vector<std::shared_ptr<AccountEntity>> entities;
	while (binder.Fetch()) {
		auto entity = make_shared<AccountEntity>(username_buffer, password_buffer);
		entities.push_back(entity);
	}

	return entities;
}