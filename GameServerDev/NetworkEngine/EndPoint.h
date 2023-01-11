#pragma once

class EndPoint
{
private:
    SOCKADDR_IN mInfo;

public:
	EndPoint();
	EndPoint(const SOCKADDR_IN& info);
	EndPoint(uint16 port);
	EndPoint(const char* ipAddress, uint16 port);

	std::string GetIpAddress() const;
	std::string GetPort() const;

	const SOCKADDR* GetSockAddr() const;
	SOCKADDR* GetSockAddr() { return (SOCKADDR*)(&mInfo); }
	
	constexpr size_t GetSize() const { return sizeof(SOCKADDR); }
	std::string ToString() const;

	static bool Resolve(const char* hostAddress, uint16 port, EndPoint& endPoint);
};