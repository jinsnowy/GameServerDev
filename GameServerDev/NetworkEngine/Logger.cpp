#include "pch.h"
#include "Logger.h"

Logger* Logger::GLogger = Logger::GetInstance();

static const wchar_t* GetTag(ELogLevel level)
{
	switch (level)
	{
	case ELogLevel::Info:
		return L"Info";
	case ELogLevel::Debug:
		return L"Debug";
	case ELogLevel::Warn:
		return L"Warn";
	case ELogLevel::Error:
		return L"Error";
	case ELogLevel::Fatal:
		return L"Fatal";
	default:
		return L"Unknown";
	}
}

Logger::Logger()
	:
	mExitFlag(false),
	mConsoleLog(true),
	mFlushDurationMilliSec(500),
	mWorker([this]() { this->flush(); }),
	mLogLevel(ELogLevel::Info)
{
	wchar_t buffer[MAX_PATH];
	::GetModuleFileNameW(NULL, buffer, MAX_PATH);

	basePath = buffer;

	size_t pos = basePath.find_last_of('\\');
	basePath = basePath.substr(0, pos);
}

Logger::~Logger()
{
	{
		std::lock_guard<std::mutex> lk(mSync);
		mExitFlag = true;
		mCV.notify_one();
	}

	if (mWorker.joinable())
	{
		mWorker.join();
	}

	if (mOutFile.is_open())
	{
		mOutFile.close();
	}
}

void Logger::SetFlushDuration(int durationMs)
{
	mFlushDurationMilliSec = durationMs;
}

void Logger::Out(ELogLevel level, std::thread::id thread_id, int line, const wchar_t* function, const wchar_t* fmt, ...)
{
	if (level < mLogLevel)
		return;

	DateTime now = DateTime::Now();

	wchar_t logBuffer[1024];
	va_list arg_ptr;
	va_start(arg_ptr, fmt);
	_vsnwprintf_s(logBuffer, std::size(logBuffer), fmt, arg_ptr);
	va_end(arg_ptr);

	size_t threadId = StdThreadId::Get();
	wstring log = logBuffer;
	wstring message = String::Format(L"[%s][%zd][%s](%d) : %s\n", now.ToString().c_str(), threadId, function, line, log.c_str());

	{
		std::lock_guard<std::mutex> lk(mSync);
		mBuffer << message;
	}
}

void Logger::write(const std::wstring& logs)
{
	try 
	{
		if (mOutFile.is_open() == false)
		{
			DateTime now = DateTime::Now();
			std::wstring log_file_name = String::Format(L"%s%d.%d.%d.log", programName.c_str(), now.Year(), now.Month(), now.Day());
			std::wstring log_file_path = String::Format(L"%s\\%s", basePath.c_str(), log_file_name.c_str());

			mOutFile.open(log_file_path, std::ios_base::out | std::ios_base::app);
		}

		if (mOutFile.is_open() == false)
		{
			return;
		}

		mOutFile << logs;
		mOutFile.flush();

		if (mConsoleLog)
		{
			std::wcout << logs;
		}
	}
	catch (std::exception e)
	{
		std::cerr << "log write failed : " << e.what() << std::endl;
	}
}

void Logger::flush()
{
	std::wstring logs;

	const auto duration = std::chrono::milliseconds(mFlushDurationMilliSec);

	while (!mExitFlag)
	{
		std::unique_lock<std::mutex> lk(mSync);

		mCV.wait_for(lk, duration, [this, &logs](){ return mExitFlag; });

		if (logs.empty())
		{
			logs = mBuffer.str();
		}

		mBuffer.str(L"");

		lk.unlock();
	
		if (!logs.empty())
		{
			write(logs);
			logs.clear();
		}
	}
}