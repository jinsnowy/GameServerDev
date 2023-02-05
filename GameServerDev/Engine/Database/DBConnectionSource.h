#pragma once

class DBTransaction;
class DBConnectionPool;
class DBConnection;
class DBStatement;

class DBConnectionSource : public enable_shared_from_this<DBConnectionSource>
{
	struct Impl;
private:
	std::unique_ptr<Impl> impl;

public:
	DBConnectionSource();
	DBConnectionSource(DBConnectionPool* poolIn, DBConnection* connIn);
	~DBConnectionSource();

	std::unique_ptr<DBStatement> CreateStatement();

	std::unique_ptr<DBTransaction> StartTransaction();

	DBConnection* Get();

	void release();
};
