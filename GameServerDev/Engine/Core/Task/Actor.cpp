#include "pch.h"
#include "Actor.h"

Actor::Actor(ExecutionContext& _exec_context)
	:
	ActorBase(_exec_context)
{
}

Actor::~Actor()
{
}

void Actor::Push(TaskPtr task)
{
	{
		StdWriteLock lk(_mtx);
		_tasks.push(std::move(task));
	}

	if (_processing.exchange(true) == false)
	{
		Submit();
	}
}

void Actor::Submit()
{
	static TaskScheduler* taskScheduler = TaskScheduler::GetInstance();

	int count;

	TaskSchedule* schedule;

	{
		StdWriteLock lk(_mtx);
		if (_tasks.empty()) {
			_processing.store(false);
			return;
		}

		count = (int)_tasks.size();

		schedule = new TaskSchedule();
		schedule->tasks = std::move(_tasks);
	}

	LOG_INFO(L"submit %d tasks", count);

	schedule->taskCreator = shared_from_this();

	taskScheduler->Schedule(schedule);
}

void Actor::PostExecute()
{
	Submit();
}