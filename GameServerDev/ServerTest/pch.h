//
// pch.h
//

#pragma once

#include "gtest/gtest.h"
#include <networkengine\CorePch.h>
#include "protocol/UserProtocolHandler.h"

#ifdef _DEBUG
#pragma comment(lib, "NetworkEngined.lib")
#pragma comment(lib, "MessageLibd.lib")
#pragma comment(lib, "libprotobufd.lib")
#else
#pragma comment(lib, "NetworkEngine.lib")
#pragma comment(lib, "MessageLib.lib")
#pragma comment(lib, "libprotobuf.lib")
#endif
#pragma comment(lib, "cryptlib.lib")
#pragma comment(lib, "Repository.lib")