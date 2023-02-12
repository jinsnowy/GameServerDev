#include "pch.h"
#include "ExecutionContext.h"
#include "../Actor/TaskQueue.h"
#include "../../Common/Config.h"

std::mutex ExecutionContext::s_process_lock = {};
std::vector<ExecutionContext*> ExecutionContext::s_exec_contexts = {};

ExecutionContext::ExecutionContext()
	:
	_cur_idx(0)
{
}

ExecutionContext::~ExecutionContext()
{
}

void ExecutionContext::Register()
{
	std::lock_guard lk(s_process_lock);
	s_exec_contexts.push_back(this);
}

void ExecutionContext::Execute(int64& time_slice)
{
	decltype(_task_queues) target_queues;

	{
		WRITE_LOCK(_mtx);

		if (_task_queues.empty()) {
			return;
		}

		target_queues = std::move(_task_queues);
	}

	if (Core::Config::debug_actor_post) {
		LOG_INFO(L"executed %p, %d", this, (int)target_queues.size());
	}

	_cur_idx = 0;

	int queue_count = (int)target_queues.size();
	while (time_slice > 0 && _cur_idx < queue_count && target_queues[_cur_idx]->Flush(time_slice)) {
		++_cur_idx;
	}

	if (_cur_idx != queue_count) {
		WRITE_LOCK(_mtx);
		for (; _cur_idx < queue_count; ++_cur_idx) {
			_task_queues.push_back(std::move(target_queues[_cur_idx]));
		}
	}
}

void ExecutionContext::Dispose()
{
}

void ExecutionContext::Enqueue(unique_ptr<TaskQueue> task_queue)
{
	WRITE_LOCK(_mtx);

	_task_queues.push_back(std::move(task_queue));
}

ExecutionContext* ExecutionContext::PostByRoundRobin(unique_ptr<TaskQueue> task_queue)
{
	static atomic<uint64> round_robin_index = 0;

	uint64 next_index = round_robin_index.fetch_add(1) % s_exec_contexts.size();

	s_exec_contexts[next_index]->Enqueue(std::move(task_queue));

	if (Core::Config::debug_actor_post) {
		LOG_INFO(L"posted to %p", s_exec_contexts[next_index]);
	}

	return s_exec_contexts[next_index];
}