#include "pch.h"
#include "ActorBase.h"

ActorBase::ActorBase(ExecutionContext& exec_context)
	:
	_exec_context(exec_context)
{
}

ExecutionContext& ActorBase::GetExecutionContext()
{
	return _exec_context;
}
