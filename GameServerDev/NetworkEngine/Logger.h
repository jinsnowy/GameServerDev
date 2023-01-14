#pragma once
#ifndef _LOGGER_H_
#define _LOGGER_H_

#include "Singleton.h"
#include "DateTime.h"

enum class ELogLevel
{
	Info,
	Debug,
	Warn,
	Error,
	Fatal,
};

class Logger : public ISingleton<Logger>
{
	friend class ISingleton<Logger>;
private:
	bool mExitFlag;
	bool mConsoleLog;
	int  mFlushDurationMilliSec;

	std::wstring basePath;
	std::wstring programName;

	std::wofstream mOutFile;
	std::wstringstream mBuffer;

	std::condition_variable mCV;
	std::thread mWorker;
	std::mutex  mSync;

	ELogLevel mLogLevel;
private:
	Logger();

public:
	~Logger();

	void SetFlushDuration(int durationMs);

	void SetConsolelogger(bool bConsolelogger) { mConsoleLog = bConsolelogger; }

	void SetloggerLevel(ELogLevel eloggerlevel) { mLogLevel = eloggerlevel; }

	void Out(ELogLevel level, std::thread::id thread_id, int line, const wchar_t* function, const wchar_t* fmt, ...);
	
private:
	void write(const std::wstring& log);

	void flush();

public:
	static Logger* GLogger;
};

#define LOG_FATAL(fmt, ...) Logger::GLogger->Out(ELogLevel::Fatal, std::this_thread::get_id(), __LINE__, __FUNCTIONW__, fmt, __VA_ARGS__)
#define LOG_ERROR(fmt, ...) Logger::GLogger->Out(ELogLevel::Error, std::this_thread::get_id(), __LINE__, __FUNCTIONW__, fmt, __VA_ARGS__)
#define LOG_WARN(fmt, ...) Logger::GLogger->Out(ELogLevel::Warn, std::this_thread::get_id(), __LINE__, __FUNCTIONW__, fmt, __VA_ARGS__)
#define LOG_DEBUG(fmt, ...) Logger::GLogger->Out(ELogLevel::Debug, std::this_thread::get_id(), __LINE__, __FUNCTIONW__, fmt, __VA_ARGS__)
#define LOG_INFO(fmt, ...) Logger::GLogger->Out(ELogLevel::Info, std::this_thread::get_id(), __LINE__, __FUNCTIONW__, fmt, __VA_ARGS__)

#endif