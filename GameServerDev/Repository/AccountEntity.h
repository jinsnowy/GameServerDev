#pragma once
#include "Engine/Core/Repository/Entity.h"

class AccountEntity : public Entity
{
public:
	AccountEntity(wstring username, wstring password);

	wstring username() { return _username; }
	wstring password() { return _password; }

private:
	wstring _username;
	wstring _password;

	DEFINE_ENTITY_API(AccountEntity, AccountRepository);
};

