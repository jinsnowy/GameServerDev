#include "pch.h"
#include "AccountRepository.h"

AccountRepository::AccountRepository()
{
}

AccountRepository::~AccountRepository()
{
}

shared_ptr<AccountEntity> AccountRepository::CreateNewAccount(DBConn& db_conn, const std::wstring& name, const wstring& password)
{
    return Create(db_conn, name, password);
}
