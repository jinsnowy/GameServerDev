#pragma once

class IoContext;
class ExecutionContext;
class DBConnection;
class ThreadContext : public IThreadStaticSingleton<ThreadContext>
{
	friend class ServiceBase;
private:
	IoContext* _io_context;
	ExecutionContext* _exec_context;
	DBConnection* _db_conn;
	atomic<bool> _disposed;

public:
	ThreadContext();
	~ThreadContext();

	ExecutionContext* GetExecutionContext() { return _exec_context; }
	IoContext* GetIoContext() { return _io_context; }
	DBConnection* GetDBConn() { return _db_conn; }

	void Process();
	void Destroy();
};