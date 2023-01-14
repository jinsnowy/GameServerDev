#pragma once

#include "MemoryPool.h"

enum IoType
{
	IO_READ,
	IO_WRITE,
	IO_CONNECT,
	IO_DISCONNECT,
	IO_ACCEPT,
};

const char* GetIoTypeStr(IoType type);

struct IoEvent : WSAOVERLAPPED
{
	IoType ioType;

	std::function<void(int32, DWORD)> task;

	template<typename T>
	IoEvent(IoType _ioType, T&& callback)
		:
		WSAOVERLAPPED{}, ioType(_ioType), task(std::forward<T>(callback)) 
	{
	}

	~IoEvent() { /*LOG_INFO(L"~IoEvent %s", getIoType(ioType)); */ }

	void operator()(int32 errorID, DWORD bytesTransferred) { task(errorID, bytesTransferred); }

	void release() { pool_delete(this); }
};

template<typename T>
IoEvent* MakeWriteTask(T&& callback) { return pool_new<IoEvent>(IO_WRITE, std::forward<T>(callback)); }

template<typename T>
IoEvent* MakeReadTask(T&& callback) { return pool_new<IoEvent>(IO_READ, std::forward<T>(callback)); }

template<typename T>
IoEvent* MakeConnectTask(T&& callback) { return pool_new<IoEvent>(IO_CONNECT, std::forward<T>(callback)); }

template<typename T>
IoEvent* MakeDisconnectTask(T&& callback) { return pool_new<IoEvent>(IO_DISCONNECT, std::forward<T>(callback)); }

template<typename T>
IoEvent* MakeAcceptTask(T&& callback) { return pool_new<IoEvent>(IO_ACCEPT, std::forward<T>(callback)); }
