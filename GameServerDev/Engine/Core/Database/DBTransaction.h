#pragma once

class DBConnection;
class DBTransaction
{
private:
	atomic<bool> committed;
	atomic<bool> rollbacked;
	DBConnection* _db_conn;

public:
	DBTransaction(DBConnection* db_conn);
	~DBTransaction();

	void Commit();
	void Rollback();
};