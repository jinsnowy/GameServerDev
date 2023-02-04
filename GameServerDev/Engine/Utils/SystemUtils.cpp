#include "pch.h"
#include "StringUtils.h"
#include "SystemUtils.h"

std::wstring SystemUtils::WSAGetLastErrorMsg()
{
	return StringUtils::ToWide(std::system_category().message(GetLastError()));
}

std::wstring SystemUtils::WSAGetLastErrorMsg(int errCode)
{
	return StringUtils::ToWide(std::system_category().message(errCode));
}