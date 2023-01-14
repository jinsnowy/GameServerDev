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
	struct LogInfo
	{
		ELogLevel level;
		wstring message;
	};

	friend class ISingleton<Logger>;
private:
	bool _consoleLog;

	std::wstring _basePath;
	std::wstring _programName;

	std::wofstream _outFile;
	std::wstringstream _buffer;

	mutex _mtx;
	vector<LogInfo> _que;
	atomic<bool> _pending;
	ELogLevel _logLevel;
private:
	Logger();

public:
	~Logger();

	void SetConsolelogger(bool bConsolelogger) { _consoleLog = bConsolelogger; }

	void SetloggerLevel(ELogLevel eloggerlevel) { _logLevel = eloggerlevel; }

	void Out(ELogLevel level, std::thread::id thread_id, int line, const wchar_t* function, const wchar_t* fmt, ...);
	
private:
	void Flush(vector<LogInfo> logs);

public:
	static Logger* GLogger;
};

#define LOG_FATAL(fmt, ...) Logger::GLogger->Out(ELogLevel::Fatal, std::this_thread::get_id(), __LINE__, __FUNCTIONW__, fmt, __VA_ARGS__)
#define LOG_ERROR(fmt, ...) Logger::GLogger->Out(ELogLevel::Error, std::this_thread::get_id(), __LINE__, __FUNCTIONW__, fmt, __VA_ARGS__)
#define LOG_WARN(fmt, ...) Logger::GLogger->Out(ELogLevel::Warn, std::this_thread::get_id(), __LINE__, __FUNCTIONW__, fmt, __VA_ARGS__)
#define LOG_DEBUG(fmt, ...) Logger::GLogger->Out(ELogLevel::Debug, std::this_thread::get_id(), __LINE__, __FUNCTIONW__, fmt, __VA_ARGS__)
#define LOG_INFO(fmt, ...) Logger::GLogger->Out(ELogLevel::Info, std::this_thread::get_id(), __LINE__, __FUNCTIONW__, fmt, __VA_ARGS__)

#endif