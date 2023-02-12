#include "pch.h"
#include "DBTransaction.h"
#include "DBConnection.h"

DBTransaction::DBTransaction(DBConnection* db_conn)
	:
	committed(false),
	rollbacked(false),
	_db_conn(db_conn)
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
		_db_conn->Commit();
	}
}

void DBTransaction::Rollback()
{
	if (rollbacked.exchange(true) == false) {
		_db_conn->Unbind();
		_db_conn->Rollback();
	}
}
