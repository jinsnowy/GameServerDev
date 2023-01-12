#pragma once
#include <memory>
#include <vector>

#include "PacketHeader.h"

using SessionPtrCRef = const std::shared_ptr<class Session>&;
using NetworkPtrCRef = const std::shared_ptr<class TcpNetwork>&;

class PacketHandler
{
public:
	virtual bool IsValidProtocol(int protocol) abstract;

	virtual void HandleRecv(NetworkPtrCRef network, const PacketHeader& header, char* buffer) {};

	virtual void HandleRecv(SessionPtrCRef session, const PacketHeader& header, char* buffer) {};

protected:
	template<typename T>
	T* Interpret(char* buffer) { return reinterpret_cast<T*>(buffer); }

	template<typename T>
	T Parse(char* buffer, int len)
	{ 
		T pkt;
		pkt.ParseFromArray(buffer + sizeof(PacketHeader), len - sizeof(PacketHeader));
		return pkt;
	}

public:
	

private:
	static std::vector<PacketHandler*> s_PacketHandler;
};