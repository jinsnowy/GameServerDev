#include "pch.h"
#include "ThreadContext.h"
#include "IoContext.h"
#include "ExecutionContext.h"
#include "../Database/DatabaseManager.h"

ThreadContext::ThreadContext()
	:
	_io_context(&IoContext::GetInstance()),
	_exec_context(&ExecutionContext::GetInstance()),
	_db_conn(nullptr)
{
	if (DatabaseManager::GetInstance().IsInitialized()) {
		_db_conn = DatabaseManager::GetInstance().GetConnection();
	}
}

ThreadContext::~ThreadContext()
{
	Destroy();
}

void ThreadContext::Process()
{
	_disposed = false;

	while (!_disposed) {
		int64 timeSliceMs = Core::Config::time_slice_exec;

		_io_context->Dispatch((DWORD)Core::Config::time_slice_io);

		_exec_context->Execute(timeSliceMs);
	}
}

void ThreadContext::Destroy()
{
	_disposed = true;
	_io_context->Dispose();
	_exec_context->Dispose();
}