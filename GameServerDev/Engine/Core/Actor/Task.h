#pragma once

#include "../Memory/PoolObject.h"

class Task
{
private:
	const wchar_t* sig;
	function<void()> func;

public:
	Task(const wchar_t* _sig, function<void()> _func) : sig(_sig), func(std::move(_func)) {}

	const wchar_t* GetTag() { return sig; }
	void operator()() { func(); }
};

template<typename F, typename T, size_t ...Is>
static void __CallFunc(F&& func, T&& tupleArgs, std::index_sequence<Is...>)
{
	std::invoke(std::forward<F>(func), std::get<Is>(tupleArgs)...);
}

static TaskPtr MakeTask(const wchar_t* sig, std::function<void()> fIn)
{
	return std::make_unique<Task>(sig, std::move(fIn));
}

template<typename F, typename ...Args>
static TaskPtr MakeTask(const wchar_t* sig, F&& fIn, Args&&... argsIn)
{
	return std::make_unique<Task>(sig, [f = std::forward<F>(fIn), tupleArgs = std::make_tuple(std::forward<Args>(argsIn)...)]() mutable
	{
		using TupleType = decltype(tupleArgs);
		__CallFunc(f, tupleArgs, std::make_index_sequence<std::tuple_size_v<TupleType>>());
	});
}

template<typename R, typename C, typename ...A, typename ...Args>
static TaskPtr MakeTask(const wchar_t* sig, R(C::* mem_func)(A...), C* inst, Args&&... argsIn)
{
	return std::make_unique<Task>(sig, [mem_func, tupleArgs = std::make_tuple(inst, std::forward<Args>(argsIn)...)]() mutable
	{
		using TupleType = decltype(tupleArgs);
		__CallFunc(mem_func, tupleArgs, std::make_index_sequence<std::tuple_size_v<TupleType>>());
	});
}

template<typename R, typename C, typename ...A, typename ...Args>
static TaskPtr MakeTask(const wchar_t* sig, R(C::* mem_func)(A...), const std::shared_ptr<C>& inst, Args&&... argsIn)
{
	return std::make_unique<Task>(sig, [mem_func, tupleArgs = std::make_tuple(inst, std::forward<Args>(argsIn)...)]() mutable
	{
		using TupleType = decltype(tupleArgs);
		__CallFunc(mem_func, tupleArgs, std::make_index_sequence<std::tuple_size_v<TupleType>>());
	});
}