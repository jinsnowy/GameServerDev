#include "pch.h"
#include "ExecutionContext.h"
#include "TaskQueue.h"

ExecutionContext::ExecutionContext()
{
}

ExecutionContext::~ExecutionContext()
{
}

void ExecutionContext::Poll(int64 timeOutMs)
{
	TaskQueue* schedule;

	while (timeOutMs > 0 && _task_que.empty() == false) 
	{
		auto task_que = _task_que.front();

		_task_que.pop();

		task_que->Flush(OUT timeOutMs);
	}
}

void ExecutionContext::Schedule(TaskQueue* schedule)
{
	_task_que.push(schedule);
}

void ExecutionContext::ReSchedule(TaskQueue* _schedule)
{
	_task_que.push(_schedule);
}

size_t ExecutionContext::TaskQueueSize()
{
	return _task_que.size();
}
