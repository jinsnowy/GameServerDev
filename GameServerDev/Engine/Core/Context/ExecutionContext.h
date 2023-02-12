#pragma once

class TaskQueue;
class ExecutionContext : public IThreadStaticSingleton<ExecutionContext>
{
	friend class ThreadContext;
	friend class Actor;
	friend class ServiceBase;
public:
	ExecutionContext();
	~ExecutionContext();

private:
	void Register();
	void Execute(int64& time_slice);
	void Dispose();
	void Enqueue(unique_ptr<TaskQueue> task_queue);
	bool Empty() const { return _task_queues.empty(); }

	static ExecutionContext* PostByRoundRobin(unique_ptr<TaskQueue> task_queue);

private:
	StdMutex _mtx;
	int _cur_idx;
	std::vector<unique_ptr<TaskQueue>> _task_queues;

	static std::mutex s_process_lock;
	static std::vector<ExecutionContext*> s_exec_contexts;
};