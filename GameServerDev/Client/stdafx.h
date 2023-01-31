#pragma once

#include <networkengine\CorePch.h>

#pragma warning( push )
#pragma warning(disable : 4946)
#pragma warning(disable : 4251)
#include "protocol/UserProtocolHandler.h"
#pragma warning( pop ) 

#ifdef _DEBUG
#pragma comment(lib, "NetworkEngined.lib")
#pragma comment(lib, "MessageLibd.lib")
#pragma comment(lib, "libprotobufd.lib")
#else
#pragma comment(lib, "NetworkEngine.lib")
#pragma comment(lib, "MessageLib.lib")
#pragma comment(lib, "libprotobuf.lib")
#endif
