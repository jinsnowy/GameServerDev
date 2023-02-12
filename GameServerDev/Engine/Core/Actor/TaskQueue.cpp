#include "pch.h"
#include "TaskQueue.h"
#include "Task.h"
#include "Actor.h"
#include "../Context/ExecutionContext.h"

TaskQueue::TaskQueue(weak_ptr<Actor> actor)
	:
	_current_index(0),
	_exec_context(nullptr),
	_actor(actor)
{
}

TaskQueue::~TaskQueue()
{
	_tasks.clear();
}

bool TaskQueue::Flush(int64& timeOutMs)
{
	Timer timer = Timer::startNew();

	while (timeOutMs > 0 && _current_index < _tasks.size())
	{
		auto task = std::move(_tasks[_current_index]);

		timer.Start();

		(*task)();

		timeOutMs -= timer.Count<std::chrono::milliseconds>();

		++_current_index;
	}

	if (auto actor = _actor.lock()) {
		actor->OnExecuteFinished();
	}

	if (_current_index != _tasks.size()) {
		return false;
	}

	_tasks.clear();

	return true;
}

void TaskQueue::Enqueue(TaskPtr&& task)
{
	_tasks.emplace_back(std::move(task));
}

bool TaskQueue::Empty()
{
	return _tasks.empty();
}
