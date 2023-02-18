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
	return DateTime(std::time(NULL));
}

DateTime DateTime::FromString(const std::wstring& str, const wchar_t* format)
{
	DateTime datetime;
	std::wstringstream wss;
	wss << str;
	wss >> std::get_time((tm*)&datetime, format);

	return datetime;
}

DateTime::DateTime(time_t t)
{
	gmtime_s((tm*)this, &t);
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

DateTime::DateTime()
{
}
