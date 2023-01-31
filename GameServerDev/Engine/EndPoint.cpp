#include "pch.h"
#include "EndPoint.h"

EndPoint::EndPoint()
	:
	mInfo{}
{
}

EndPoint::EndPoint(const SOCKADDR_IN& info)
    :
    mInfo(info)
{
}

EndPoint::EndPoint(uint16 port)
{
	mInfo.sin_family = AF_INET;
	mInfo.sin_addr.s_addr = htonl(INADDR_ANY);
	mInfo.sin_port = htons(port);
}

EndPoint::EndPoint(const char* ipAddress, uint16 port)
{
    mInfo.sin_family = AF_INET;
    mInfo.sin_addr.s_addr = inet_addr(ipAddress);
    mInfo.sin_port = htons(port);
}

std::wstring EndPoint::GetIpAddress() const
{
	return String::ToWide(inet_ntoa(mInfo.sin_addr));
}

std::wstring EndPoint::GetPort() const
{
	return std::to_wstring(ntohs(mInfo.sin_port));
}

const SOCKADDR* EndPoint::GetSockAddr() const
{
	return (const SOCKADDR*)(&mInfo);
}

std::wstring EndPoint::ToString() const
{
	return String::Format(L"%s:%s", GetIpAddress().c_str(), GetPort().c_str());
}

bool EndPoint::Resolve(const char* hostAddress, uint16 port, EndPoint& endPoint)
{
	addrinfo* result = nullptr;
	addrinfo hints = {};
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;

	auto err_code = getaddrinfo(hostAddress, std::to_string(port).c_str(), &hints, &result);
	if (err_code != 0 || result == nullptr)
	{
		return false;
	}

	SOCKADDR_IN* address = (SOCKADDR_IN*)(result->ai_addr);
	endPoint = EndPoint(*address);
	freeaddrinfo(result);

	return true;
}
