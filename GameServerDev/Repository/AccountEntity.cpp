#include "pch.h"
#include "AccountEntity.h"
#include "Engine/Core/Database/DBUtils.h"

AccountEntity::AccountEntity(wstring username, wstring password)
	:
	_username(username),
	_password(password)
{
}

CREATE_API(AccountEntity)
{
	auto stmt = db_conn->CreateStatement();

	auto handle = stmt->GetHandle();

	int32 id = 0;
	stmt->BindParam(_username);
	stmt->BindParam(_password);
	stmt->BindResult(id);

	stmt->Execute(L"usp_CreateAccount");

	if (stmt->Success() == false) {
		return false;
	}

	if (stmt->FetchResult())
	{
		_id = id;

		return true;
	}

	return false;
}

REMOVE_API(AccountEntity)
{
	int id = _id.load();

	auto stmt = db_conn->CreateStatement();
	stmt->BindParam(id);
	stmt->Execute(L"usp_DeleteAccount");

	if (stmt->Success() == false) {
		return false;
	}

	return true;
}

UPDATE_API(AccountEntity)
{
	return true;
}

SELECT_API(AccountEntity)
{
	auto stmt = db_conn->CreateStatement();
	stmt->BindParam(id);

	wchar_t username_buffer[512];
	wchar_t password_buffer[512];

	stmt->Execute(L"usp_SelectAccount");
	if (stmt->Success() == false) {
		return nullptr;
	}

	stmt->BindResult(username_buffer);
	stmt->BindResult(password_buffer);

	if (stmt->FetchResult()) {
		auto entity = make_shared<AccountEntity>(username_buffer, password_buffer);
		entity->_id = id;
		return entity;
	}

	return nullptr;
}

SELECT_ALL_API(AccountEntity)
{
	auto stmt = db_conn->CreateStatement();

	wchar_t username_buffer[512];
	wchar_t password_buffer[512];

	stmt->Execute(L"usp_SelectAllAccount");
	if (stmt->Success() == false) {
		return {};
	}

	stmt->BindResult(username_buffer);
	stmt->BindResult(password_buffer);

	std::vector<std::shared_ptr<AccountEntity>> entities;

	while (stmt->FetchResult()) {
		auto entity = make_shared<AccountEntity>(username_buffer, password_buffer);
		entities.push_back(entity);
	}

	return entities;
}