#pragma once

class DBConnectionSource;
class DBTransaction
{
private:
	atomic<bool> committed;
	atomic<bool> rollbacked;
	shared_ptr<DBConnectionSource> connSource;

public:
	DBTransaction(shared_ptr<DBConnectionSource> connSourceIn);
	~DBTransaction();

	void Commit();
	void Rollback();
};