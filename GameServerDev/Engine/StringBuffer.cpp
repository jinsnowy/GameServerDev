#include "pch.h"
#include "StringBuffer.h"
#include "Utils.h"

StringBuffer::StringBuffer()
{
	Utils::Init(buffer);
	len = 0;
}

void StringBuffer::Set(const wstring& target)
{
	Utils::CopyStr(buffer, target);
	len = target.size();
}

void StringBuffer::Set(const wchar_t* str)
{
	Utils::CopyStr(buffer, str);
	len = lstrlenW(str);
}

void StringBuffer::CopyFrom(const StringBuffer rhs)
{
	wmemcpy_s(buffer, BUFFER_SIZE, rhs.buffer, rhs.len);
	len = rhs.len;
}

wstring StringBuffer::ToString()
{
	return Utils::Slice(buffer, len);
}

bool StringBuffer::Equal(const StringBuffer& rhs)
{
	wstring s1 = Utils::Slice(buffer, len);
	wstring s2 = Utils::Slice(rhs.buffer, rhs.len);

	return s1 == s2;
}

bool StringBuffer::Equal(const wstring& rhs)
{
	wstring s = Utils::Slice(buffer, len);
	return s == rhs;
}