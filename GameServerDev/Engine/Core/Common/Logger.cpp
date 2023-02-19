#include "pch.h"
#include "Logger.h"
#include "Utils/StringUtils.h"
#include <io.h>
#include <fcntl.h>

Logger* Logger::GLogger = &Logger::GetInstance();

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
	_consoleLog(true),
	_pending(false)
{
	wchar_t buffer[MAX_PATH];
	::GetModuleFileNameW(NULL, buffer, MAX_PATH);

	_basePath = buffer;

	size_t pos = _basePath.find_last_of('\\');
	_basePath = _basePath.substr(0, pos);

	_setmode(_fileno(stdout), _O_U16TEXT);

	try
	{
		DateTime now = DateTime::Now();
		std::wstring log_file_name = StringUtils::Format(L"%s%d.%d.%d.log", _programName.c_str(), now.Year(), now.Month(), now.Day());
		std::wstring log_file_path = StringUtils::Format(L"%s\\%s", _basePath.c_str(), log_file_name.c_str());

		_outFile.open(log_file_path, std::ios_base::out | std::ios_base::app);
	}
	catch (std::exception e)
	{
		std::cerr << "open file failed : " << e.what() << std::endl;
	}
}

Logger::~Logger()
{
	if (_outFile.is_open())
	{
		_outFile.close();
	}
}

void Logger::Out(ELogLevel level, std::thread::id thread_id, int line, const wchar_t* function, const wchar_t* fmt, ...)
{
	if (level < _logLevel)
		return;

	DateTime now = DateTime::Now();

	wchar_t logBuffer[1024];
	va_list arg_ptr;
	va_start(arg_ptr, fmt);
	_vsnwprintf_s(logBuffer, std::size(logBuffer), fmt, arg_ptr);
	va_end(arg_ptr);

	int threadId = ThreadId::Get();
	wstring message = StringUtils::Format(L"[%s][%d][%s][%s](%d) : %s", now.ToString().c_str(), threadId, GetTag(level), function, line, logBuffer);

	try
	{
		_outFile << message << std::endl;
		_outFile.flush();

		if (_consoleLog) {
			HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
			CONSOLE_SCREEN_BUFFER_INFO PrevInfo;
			GetConsoleScreenBufferInfo(hConsole, &PrevInfo);
			switch (level)
			{
			case ELogLevel::Fatal:
				SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_INTENSITY);
				break;
			case ELogLevel::Error:
				SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
				break;
			case ELogLevel::Warn:
				SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE);
				break;
			case ELogLevel::Debug:
				SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN);
				break;
			}
			
			std::wcout << message << std::endl;
			SetConsoleTextAttribute(hConsole, PrevInfo.wAttributes);
		}
	}
	catch (std::exception e)
	{
		std::cerr << "log write failed : " << e.what() << std::endl;
	}

}

void Logger::Flush(vector<LogInfo> logs)
{
	try 
	{
		for (const auto& logInfo : logs)
		{
			_outFile << logInfo.message;

			if (_consoleLog)
			{
				std::wcout << logInfo.message;
			}
		}

		_outFile.flush();
		if (_consoleLog) {
			std::wcout.flush();
		}
	}
	catch (std::exception e)
	{
		std::cerr << "log write failed : " << e.what() << std::endl;
	}

	_pending.store(false);
}