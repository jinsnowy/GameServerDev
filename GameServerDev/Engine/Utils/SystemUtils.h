#pragma once

class SystemUtils
{
public:
	static std::wstring WSAGetLastErrorMsg();
	static std::wstring WSAGetLastErrorMsg(int errCode);

	template<size_t sz>
	static void Zero(wchar_t(&buffer)[sz])
	{
		ZeroMemory(buffer, sizeof(buffer));
	}

	template<size_t sz>
	static void Zero(char(&buffer)[sz])
	{
		ZeroMemory(buffer, sizeof(buffer));
	}
};