//
// pch.h
//

#pragma once

#include "gtest/gtest.h"

#include <Engine/Core/CorePch.h>

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
