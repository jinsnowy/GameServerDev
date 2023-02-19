#include "pch.h"
#include "IoEvent.h"

namespace Core {
	namespace Network {
		namespace IO {
			const char* GetIoTypeStr(IoType type)
			{
				switch (type)
				{
				case IoType::IO_READ:
					return "IoType::IO_READ";
				case IoType::IO_WRITE:
					return "IoType::IO_WRITE";
				case IoType::IO_CONNECT:
					return "IoType::IO_CONNECT";
				case IoType::IO_DISCONNECT:
					return "IoType::IO_DISCONNECT";
				case IoType::IO_ACCEPT:
					return "IoType::IO_ACCEPT";
				default:
					return "IO_NONE";
				}
			}
		}
	}
}