#pragma once
#include <iostream>
#include <iomanip>
#include <ctime>
#include <sstream>

class DateTime : protected tm
{
public:
	static DateTime Now();
	static DateTime UtcNow();
	static DateTime FromString(const std::wstring& str, const wchar_t* format = L"%Y-%m-%d %H:%M:%S");
	
	DateTime(time_t t);

	int Year() const { return tm_year + 1900; }
	int Day() const { return tm_mday; }
	int Month() const { return tm_mon + 1; }

	std::wstring ToString(const wchar_t* format = L"%Y-%m-%d %H:%M:%S") const;
	std::wstring ToSqlString() const;

	

private:
	DateTime();
};