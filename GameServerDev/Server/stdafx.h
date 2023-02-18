#pragma once


#include <Engine/Core/CorePch.h>
#include "protocol/UserHandler.h"

#ifdef _DEBUG
#pragma comment(lib, "Engined.lib")
#pragma comment(lib, "MessageLibd.lib")
#pragma comment(lib, "libprotobufd.lib")
#else
#pragma comment(lib, "Engine.lib")
#pragma comment(lib, "MessageLib.lib")
#pragma comment(lib, "libprotobuf.lib")
#endif

#pragma comment(lib, "cryptlib.lib")
#pragma comment(lib, "Repository.lib")