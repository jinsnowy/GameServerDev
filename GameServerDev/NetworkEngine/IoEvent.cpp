#include "pch.h"
#include "IoEvent.h"

const char* GetIoTypeStr(IoType type)
{
	switch (type)
	{
	case IO_READ:
		return "IO_READ";
	case IO_WRITE:
		return "IO_WRITE";
	case IO_CONNECT:
		return "IO_CONNECT";
	case IO_DISCONNECT:
		return "IO_DISCONNECT";
	case IO_ACCEPT:
		return "IO_ACCEPT";
	default:
		return "IO_NONE";
	}
}
