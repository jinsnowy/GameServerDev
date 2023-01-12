#include "pch.h"
#include "Utils.h"

std::string Utils::WSAGetLastErrorMsg()
{
	int errorMessageID = ::WSAGetLastError();
	char buf[1024];
	FormatMessageA(FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
		NULL, errorMessageID, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		buf, (sizeof(buf) / sizeof(char)), NULL);

	return buf;
}

std::string Utils::WSAGetLastErrorMsg(int errCode)
{
	char buf[1024];
	FormatMessageA(FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
		NULL, errCode, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		buf, (sizeof(buf) / sizeof(char)), NULL);

	return buf;
}