#pragma once

struct LessNextTick
{
	bool operator()(const AlarmPtr& lhs, const AlarmPtr& rhs);
};

class Alarm : public enable_shared_from_this<Alarm>
{
	friend class AlarmManager;
	friend struct LessNextTick;
public:
	Alarm(const string& tag, uint32 periodMs, TaskPtr task, bool periodic);

	virtual ~Alarm();

	bool TimeToExecute(const uint64& tick) { return _nextTick <= tick; }

	const string& GetTag() { return _tag; }

	uint32 GetPeriod() { return _periodMs; }

	bool IsPeriodic() { return _periodic; }

	bool IsEnabled() { return _enabled; }

	uint64 GetNextTick() { return _nextTick; }

	void Disable();

	static AlarmPtr Create(const string& tag, uint32 periodMs, TaskPtr task, bool periodic = true);

private:
	void Execute();

private:
	bool			 _periodic;
	TaskPtr			 _task;
	atomic<bool>     _enabled;
	string		     _tag;
	uint32			 _periodMs;
	uint64		     _nextTick;

public:
	template<typename F, typename ...Args>
	static void Register(string tag, uint32 periodMs, bool periodic, F&& fIn, Args&&... argsIn)
	{
		Register(tag, periodMs, MakeTask(std::forward<F>(fIn), std::forward<Args>(argsIn)...), periodic);
	}

	static void Register(string tag, uint32 periodMs, TaskPtr task, bool periodic = true);
	static void Remove(string tag);
};