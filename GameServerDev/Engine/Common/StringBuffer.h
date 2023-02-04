#pragma once

struct StringBuffer
{
	enum
	{
		BUFFER_SIZE = 512
	};

	wchar_t buffer[BUFFER_SIZE];
	size_t len;

	StringBuffer();

	void Set(const wstring& target);

	void Set(const wchar_t* str);

	void CopyFrom(const StringBuffer rhs);

	wstring ToString();

	bool Equal(const StringBuffer& rhs);

	bool Equal(const wstring& rhs);
};