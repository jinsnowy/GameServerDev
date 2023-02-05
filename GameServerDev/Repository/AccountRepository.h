#pragma once
#include "AccountEntity.h"
#include "Engine/Core/Repository/PersistentRepository.h"

class AccountRepository : public PersistentRepository<AccountEntity>
{
public:
	AccountRepository();

	~AccountRepository();

	shared_ptr<AccountEntity> CreateNewAccount(DBConn& db_conn, const std::wstring& name, const wstring& password);
};
