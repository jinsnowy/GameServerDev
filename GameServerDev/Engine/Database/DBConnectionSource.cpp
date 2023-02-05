#include "pch.h"
#include "DBConnectionSource.h"
#include "DBConnection.h"
#include "DBConnectionPool.h"
#include "DBTransaction.h"
#include "DBStatement.h"

struct DBConnectionSource::Impl
{
	DBConnectionPool * pool;
	DBConnection* conn;

	Impl(DBConnectionPool* poolIn, DBConnection* connIn);
	~Impl();
};

DBConnectionSource::DBConnectionSource()
{
}

DBConnectionSource::DBConnectionSource(DBConnectionPool* poolIn, DBConnection* connIn)
	:
	impl(std::make_unique<Impl>(poolIn, connIn))
{}

DBConnectionSource::~DBConnectionSource()
{
}

std::unique_ptr<DBStatement> DBConnectionSource::CreateStatement()
{
	return std::make_unique<DBStatement>(shared_from_this());
}

std::unique_ptr<DBTransaction> DBConnectionSource::StartTransaction()
{
	impl->conn->BeginTransaction();
	return std::make_unique<DBTransaction>(shared_from_this());
}

DBConnection* DBConnectionSource::Get()
{
	return impl->conn;
}

void DBConnectionSource::release()
{
	impl.reset();
}

DBConnectionSource::Impl::Impl(DBConnectionPool* poolIn, DBConnection* connIn)
	:
	pool(poolIn),
	conn(connIn)
{
}

DBConnectionSource::Impl::~Impl()
{
	pool->Push(conn);
}