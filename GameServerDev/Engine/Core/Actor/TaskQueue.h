#pragma once

#include "../Memory/PoolObject.h"

class Actor;
class Task;
class ExecutionContext;
class TaskQueue
{
	friend class TaskScheduler;
public:
	int	_current_index;
	vector<std::unique_ptr<Task>> _tasks;
	weak_ptr<Actor> _actor;
	ExecutionContext* _exec_context;
	StdMutex _mutex;

public:
	TaskQueue(weak_ptr<Actor> actor);
	~TaskQueue();

	bool Flush(int64& timeOutMs);
	void Enqueue(TaskPtr&& task);
	bool Empty();
};
