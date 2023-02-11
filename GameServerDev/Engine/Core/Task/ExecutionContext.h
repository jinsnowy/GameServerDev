#pragma once

class TaskQueue;
class ExecutionContext
{
public:
	ExecutionContext();
	~ExecutionContext();

	void Poll(int64 timeOutMs);

	void Schedule(TaskQueue* schedule);

	void ReSchedule(TaskQueue* _schedule);

	size_t TaskQueueSize();

private:
	queue<TaskQueue*> _task_que;
};