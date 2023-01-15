//
// pch.h
//

#pragma once

#include "gtest/gtest.h"
#include "CorePch.h"

#ifdef _DEBUG
#pragma comment(lib, "NetworkEngined.lib")
#else
#pragma comment(lib, "NetworkEngine.lib")
#endif
