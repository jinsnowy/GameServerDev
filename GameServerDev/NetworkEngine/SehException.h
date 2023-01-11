#pragma once

#include <eh.h>
#include <exception>

class SehException : public std::exception
{
private:
	const unsigned int nSE;

public:
	SehException() noexcept;

	SehException(unsigned int n) noexcept;

	unsigned int GetSeNumber() const noexcept { return nSE; }

private:
	const char* GetMessage(unsigned int code);
};

class SehExceptionHandler
{
private:
	const _se_translator_function old_SE_translator;

public:
	SehExceptionHandler(_se_translator_function new_SE_translator) noexcept;

	~SehExceptionHandler() noexcept;

	SehExceptionHandler();

private:
	static void Install();

	static void OnException(unsigned int u, EXCEPTION_POINTERS*);
};