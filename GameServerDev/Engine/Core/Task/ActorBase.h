#pragma once

class ExecutionContext;
class ActorBase : public enable_shared_from_this<ActorBase>
{
private:
	ExecutionContext& _exec_context;

public:
	ActorBase(ExecutionContext& exec_context);

	ExecutionContext& GetExecutionContext();

	virtual void Submit() abstract;

	virtual void PostExecute() abstract;
};
