#include "pch.h"
#include "TaskSchedule.h"
#include "TaskScheduler.h"
#include "TaskSerializer.h"

TaskSchedule::TaskSchedule()
{
}

TaskSchedule::TaskSchedule(shared_ptr<ITaskCreator> _creator)
	:
	taskCreator(_creator)
{
}

TaskSchedule::TaskSchedule(shared_ptr<ITaskCreator> _creator, queue<TaskPtr> _tasks)
	:
	taskCreator(_creator),
	tasks(std::move(_tasks))
{
}

TaskSchedule::~TaskSchedule()
{
}

void TaskSchedule::Flush(int64& timeOutMs)
{
	static TaskScheduler* scheduler = TaskScheduler::GetInstance();

	thread_local Timer timer = Timer::startNew();

	// LOG_INFO(L"Enter %llu tasks", tasks.size());

	while (timeOutMs > 0 && tasks.empty() == false)
	{
		auto task = std::move(tasks.front());
		tasks.pop();

		timer.Start();

		(*task)();

		timeOutMs -= timer.Count<std::chrono::milliseconds>();
	}

	// LOG_INFO(L"Leave %llu tasks", tasks.size());
	
	if (tasks.empty() == false)
	{
		scheduler->ReSchedule(this);
	}
	else
	{
		Done();
	}
}

void TaskSchedule::Done()
{
	if (taskCreator) {
		taskCreator->PostExecute();
	}

	delete this;
}