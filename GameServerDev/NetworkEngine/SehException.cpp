#include "pch.h"
#include "SehException.h"

SehException::SehException() noexcept
	: 
	SehException{ 0 } 
{
}

SehException::SehException(unsigned int n) noexcept
	: 
	nSE{ n }, std::exception(GetMessage(n)) 
{
}

const char* SehException::GetMessage(unsigned int code)
{
	static char buffer[128];
	memset(buffer, 0, std::size(buffer));
	snprintf(buffer, std::size(buffer), "SEHException Code : (%d)", code);

	return buffer;
}

SehExceptionHandler::SehExceptionHandler(_se_translator_function new_SE_translator) noexcept
	: 
	old_SE_translator{ _set_se_translator(new_SE_translator) } 
{}

SehExceptionHandler::~SehExceptionHandler() noexcept
{
	_set_se_translator(old_SE_translator);
}

SehExceptionHandler::SehExceptionHandler()
	:
	SehExceptionHandler(OnException)
{}

void SehExceptionHandler::Install()
{
	thread_local SehExceptionHandler exceptionHandler;
}

void SehExceptionHandler::OnException(unsigned int u, EXCEPTION_POINTERS*)
{
	throw SehException(u);
}
