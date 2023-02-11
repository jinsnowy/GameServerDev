#include "pch.h"
#include "IntegrateTest.h"

#include "Repository/AccountRepository.h"
#include "Engine/Core/Repository/EntityException.h"

namespace IntegrateTestSuite
{
	class AccountIntegrateTest : public IntegrateTest
	{
	protected:
		AccountRepository repository;

	public:
		shared_ptr<AccountEntity> Create(wstring u, wstring p)
		{
			return repository.Create(dbConn, u, p);
		}
	};

	TEST_F(AccountTest, Account_����_����_�׽�Ʈ) 
	{
		auto transaction = dbConn->StartTransaction();

		wstring my_username = L"hello";
		wstring my_password = L"world";

		auto account = Create(my_username, my_password);

		ASSERT_TRUE(account != nullptr);
		ASSERT_TRUE(account->username() == my_username);
		ASSERT_TRUE(account->password() == my_password);

		LOG_INFO(L"���� �׽�Ʈ ���� ����");

		transaction->Rollback();
	}

}