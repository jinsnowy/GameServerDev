#pragma once

#include "ActorBase.h"

class ExecutionContext;
class Actor : public ActorBase
{
	friend class ExecutionContext;
public:
	Actor(ExecutionContext& _exec_context);
	virtual ~Actor();

public:
	template<typename R, typename T, typename ...Args>
	void Enqueue(R(T::* mem_func)(Args...), Args... args)
	{
		shared_ptr<T> obj = static_pointer_cast<T>(shared_from_this());
		Push(MakeTask(mem_func, obj, std::forward<Args>(args)...));
	}

private:
	atomic<bool>     _processing;
	queue<TaskPtr>   _tasks;

private:
	void Push(TaskPtr task);

	virtual void Submit() override;
	virtual void PostExecute() override;
};