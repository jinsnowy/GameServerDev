#include "pch.h"
#include "StringBuffer.h"
#include "Utils/SystemUtils.h"

StringBuffer::StringBuffer()
{
	SystemUtils::Zero(buffer);
	len = 0;
}

void StringBuffer::Set(const wstring& target)
{
	StringUtils::CopyStr(buffer, target);
	len = target.size();
}

void StringBuffer::Set(const wchar_t* str)
{
	StringUtils::CopyStr(buffer, str);
	len = lstrlenW(str);
}

void StringBuffer::CopyFrom(const StringBuffer rhs)
{
	wmemcpy_s(buffer, BUFFER_SIZE, rhs.buffer, rhs.len);
	len = rhs.len;
}

wstring StringBuffer::ToString()
{
	return StringUtils::Slice(buffer, len);
}

bool StringBuffer::Equal(const StringBuffer& rhs)
{
	wstring s1 = StringUtils::Slice(buffer, len);
	wstring s2 = StringUtils::Slice(rhs.buffer, rhs.len);

	return s1 == s2;
}

bool StringBuffer::Equal(const wstring& rhs)
{
	wstring s = StringUtils::Slice(buffer, len);
	return s == rhs;
}