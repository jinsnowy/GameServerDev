#include "pch.h"
#include "Actor.h"
#include "../Context/ExecutionContext.h"
#include "Task.h"
#include "TaskQueue.h"

Actor::Actor()
	:
	_task_queue(nullptr),
	_executing(false)
{
}

Actor::~Actor()
{
	delete _task_queue;
}

void Actor::Post()
{
	WRITE_LOCK(_mtx);

	auto prev = _task_queue;

	if (_task_queue->Empty() == false)
	{
		_task_queue = new TaskQueue(shared_from_this());

		_context = ExecutionContext::PostByRoundRobin(std::unique_ptr<TaskQueue>(prev));

		_executing = true;
	}
	else {
		_executing = false;
	}
}

void Actor::Enqueue(TaskPtr task)
{
	{
		WRITE_LOCK(_mtx);

		if (_task_queue == nullptr) {
			_task_queue = new TaskQueue(shared_from_this());
		}

		_task_queue->Enqueue(std::move(task));
	}

	Post();
}

void Actor::OnExecuteFinished()
{
	Post();
}