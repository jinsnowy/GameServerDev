#include "pch.h"

DateTime DateTime::Now()
{
	auto t = std::time(NULL);
	auto date = DateTime();
	localtime_s((tm*)&date, &t);

	return date;
}

DateTime DateTime::UtcNow()
{
	auto t = std::time(NULL);
	auto date = DateTime();
	gmtime_s((tm*)&date, &t);

	return date;
}

std::wstring DateTime::ToString(const wchar_t* format) const
{
	std::wostringstream oss;
	oss << std::put_time((tm*)this, format);
	return oss.str();
}

std::wstring DateTime::ToSqlString() const
{
	return ToString(L"%Y-%m-%d %H:%M:%S");
}