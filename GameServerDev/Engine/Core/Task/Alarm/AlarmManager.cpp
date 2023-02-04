#include "pch.h"
#include "AlarmManager.h"
#include "Core/Task/TaskSchedule.h"
#include "Core/Task/TaskScheduler.h"

AlarmManager::AlarmManager()
{
	_shorttermScheduler = make_shared<AlarmManager::AlarmScheduler>(
	[](TaskSchedule* schedule) {
		TaskScheduler::GetInstance()->HighPrioritySchedule(schedule);
	});

	_longtermScheduler = make_shared<AlarmManager::AlarmScheduler>(
	[](TaskSchedule* schedule) {
		TaskScheduler::GetInstance()->Schedule(schedule);
	});
}

AlarmManager::~AlarmManager()
{
}

AlarmManager::AlarmScheduler::AlarmScheduler(function<void(TaskSchedule*)> schedule_func)
	:
	_pending(false),
	_schedule_func(schedule_func)
{
	_schedule_holder = new TaskSchedule();
}

AlarmManager::AlarmScheduler::~AlarmScheduler() {
	delete _schedule_holder;
}

void AlarmManager::Register(AlarmPtr alarm)
{
	if (!AddAlarm(alarm))
		return;
	
	if (alarm->GetPeriod() < LongPeriodAlarmMs) {
		_shorttermScheduler->Push(alarm);
	}
	else {
		_longtermScheduler->Push(alarm);
	}
}

void AlarmManager::AlarmScheduler::Push(AlarmPtr alarm)
{
	{
		StdWriteLock lk(_mtx);
		_alarm_que.push(alarm);
	}

	if (_pending.exchange(true) == false) {
		Submit();
	}
}

void AlarmManager::AlarmScheduler::Execute(AlarmQueue& alarmQueue)
{
	uint64 curTick = ::GetTickCount64();

	while (alarmQueue.empty() == false) {
		auto alarm = alarmQueue.top();
		alarmQueue.pop();

		if (alarm->TimeToExecute(curTick)) {
			alarm->Execute();
		}

		if (alarm->IsEnabled()) {
			Reschedule(alarm);
		}
	}
}

void AlarmManager::AlarmScheduler::Submit()
{
	TaskSchedule* submittedSchedule = nullptr;

	{
		StdWriteLock lk(_mtx);
		if (_alarm_que.empty()) {
			_pending.store(false);
			return;
		}
		
		submittedSchedule = _schedule_holder;

		_schedule_holder = new TaskSchedule();
	}

	submittedSchedule->tasks.push(MakeTask(&AlarmManager::AlarmScheduler::Execute, this, std::move(_alarm_que)));
	submittedSchedule->taskCreator = shared_from_this();

	_schedule_func(submittedSchedule);
}

void AlarmManager::AlarmScheduler::Reschedule(AlarmPtr alarm)
{
	StdWriteLock lk(_mtx);
	_alarm_que.push(alarm);
}

void AlarmManager::AlarmScheduler::PostExecute()
{
	Submit();
}

bool AlarmManager::AddAlarm(AlarmPtr alarm)
{
	const string& tag = alarm->GetTag();

	StdWriteLock lk(_mtx);
	if (_alarms.find(tag) != _alarms.end()) {
		LOG_ERROR(L"failed to register : tag %s exists", tag.c_str());
		return false;
	}

	_alarms[tag] = alarm;

	return true;
}

void AlarmManager::RemoveAlarm(const string& tag)
{
	StdWriteLock lk(_mtx);
	auto iter = _alarms.find(tag);
	if (iter == _alarms.end()) {
		return;
	}

	_alarms.erase(iter);
}
