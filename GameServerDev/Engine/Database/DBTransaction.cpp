#include "pch.h"
#include "DBTransaction.h"
#include "DBConnection.h"
#include "DBConnectionSource.h"

DBTransaction::DBTransaction(shared_ptr<DBConnectionSource> connSourceIn)
	:
	committed(false),
	rollbacked(false),
	connSource(connSourceIn)
{
}

DBTransaction::~DBTransaction()
{
	if (committed == false) {
		Rollback();
	}
}

void DBTransaction::Commit()
{
	if (committed.exchange(true) == false) {
		connSource->Get()->Commit();
	}
}

void DBTransaction::Rollback()
{
	if (rollbacked.exchange(true) == false) {
		connSource->Get()->Unbind();
		connSource->Get()->Rollback();
	}
}
