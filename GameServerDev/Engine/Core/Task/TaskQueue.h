#pragma once

#include "Task.h"
#include "Actor.h"

class TaskQueue : public PoolObject
{
	friend class TaskScheduler;
public:
	std::queue<TaskPtr> tasks;
	std::shared_ptr<Actor> taskCreator;

public:
	TaskQueue();
	TaskQueue(shared_ptr<Actor> _creator);
	TaskQueue(shared_ptr<Actor> _creator, queue<TaskPtr> _tasks);

	void Flush(int64& timeOutMs);

private:
	void Done();
};
