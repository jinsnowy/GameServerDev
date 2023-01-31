#pragma once
#include <chrono>
#include <ctime>

class Timer
{
	using Clock = std::chrono::steady_clock;
	using TimePoint = std::chrono::steady_clock::time_point;
private:
	TimePoint mStart;
	Timer() : mStart(Clock::now()) {}

public:
	static Timer startNew() noexcept { return Timer(); }

	void Start() { mStart = Clock::now(); }

	template<typename T>
	auto Count() const
	{
		return std::chrono::duration_cast<T>(Clock::now() - mStart).count();
	}

	template<typename T>
	static auto Count(const TimePoint& start)
	{
		return std::chrono::duration_cast<T>(Clock::now() - start).count();
	}
};