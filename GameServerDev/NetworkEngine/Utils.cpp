#include "pch.h"
#include "Utils.h"

std::wstring Utils::WSAGetLastErrorMsg()
{
	return String::ToWide(std::system_category().message(GetLastError()));
}

std::wstring Utils::WSAGetLastErrorMsg(int errCode)
{
	return String::ToWide(std::system_category().message(errCode));
}