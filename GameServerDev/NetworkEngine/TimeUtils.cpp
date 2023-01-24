#include "pch.h"
#include "TimeUtils.h"

time_t TimeUtils::UtcNow()
{
    return time(NULL);
}

tm TimeUtils::ToStruct(time_t t)
{
    struct tm st;
    gmtime_s(&st, &t);
    return st;
}

DateTime TimeUtils::ToDateTime(time_t t)
{
    return DateTime(t);
}

int TimeUtils::Diff(time_t from, time_t to)
{
    return to - from;
}

int TimeUtils::DiffAbs(time_t from, time_t to)
{
    return abs(to - from);
}
