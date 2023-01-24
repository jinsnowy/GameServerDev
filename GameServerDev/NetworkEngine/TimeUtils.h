#pragma once

#include "DateTime.h"

class TimeUtils
{
public:
	static time_t UtcNow();
	static struct tm ToStruct(time_t t);
	static DateTime ToDateTime(time_t t);

	static int Diff(time_t from, time_t to);
	static int DiffAbs(time_t from, time_t to);
};

