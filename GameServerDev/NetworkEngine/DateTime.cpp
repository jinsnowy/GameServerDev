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

std::string DateTime::ToString(const char* format) const
{
	std::ostringstream oss;
	oss << std::put_time((tm*)this, format);
	return oss.str();
}

std::string DateTime::ToSqlString() const
{
	return ToString("%Y-%m-%d %H:%M:%S");
}