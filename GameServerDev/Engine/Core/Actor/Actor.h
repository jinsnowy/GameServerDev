#pragma once

#include "Task.h"

class ExecutionContext;
class TaskQueue;

class Actor : public enable_shared_from_this<Actor>
{
	friend class TaskQueue;
public:
	Actor();
	virtual ~Actor();

public:
	template<typename R, typename T, typename ...Args>
	void Enqueue(const wchar_t* sig, R(T::* mem_func)(Args...), Args... args)
	{
		shared_ptr<T> obj = static_pointer_cast<T>(shared_from_this());
		Enqueue(MakeTask(sig, mem_func, obj, std::forward<Args>(args)...));
	}

	template<typename T, typename F>
	void Enqueue(const wchar_t* sig, F&& then) {
		Enqueue(MakeTask(sig, then, static_pointer_cast<T>(shared_from_this())));
	}

private:
	StdMutex _mtx;
	bool	_executing;
	ExecutionContext* _context;
	TaskQueue* _task_queue;

private:
	void Post();
	void Enqueue(TaskPtr task);
	void OnExecuteFinished();
};

#define ENQUEUE_MEM(mem_func, ...) Enqueue(__FUNCTIONW__, mem_func, ##__VA_ARGS__)
#define ENQUEUE(T, then) Enqueue<T>(__FUNCTIONW__, then)