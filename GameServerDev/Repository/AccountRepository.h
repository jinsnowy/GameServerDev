#pragma once
#include "AccountEntity.h"
#include "PersistentRepository.h"

class AccountRepository : public PersistentRepository<AccountEntity>
{
public:
	AccountRepository();
	~AccountRepository();
};
