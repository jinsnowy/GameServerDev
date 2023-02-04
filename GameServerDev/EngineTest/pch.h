//
// pch.h
//

#pragma once

#include "gtest/gtest.h"

#include "Engine/Core/CorePch.h"

#ifdef _DEBUG
#pragma comment(lib, "Engined.lib")
#else
#pragma comment(lib, "Engine.lib")
#endif
