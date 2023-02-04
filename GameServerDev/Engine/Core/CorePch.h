#pragma once

// 여기에 미리 컴파일하려는 헤더 추가
#include "framework.h"

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>

#include <algorithm>
#include <bitset>
#include <mutex>
#include <memory>
#include <functional>
#include <thread>
#include <future>
#include <string>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <type_traits>
#include <chrono>
#include <random>
#include <shared_mutex>

#include "CoreStl.h"

using namespace std;

#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <mswsock.h>
#include <rpc.h>

#include "CoreMacro.h"
#include "CoreDefine.h"
#include "CoreStruct.h"

#ifdef _ENGINE
#include "Common/Common.h"
#include "Types/Types.h"
#include "Utils/Utils.h"
#else
#include "Engine/Common/Common.h"
#include "Engine/Types/Types.h"
#include "Engine/Utils/Utils.h"
#endif

#pragma comment(lib, "Rpcrt4.lib")
#pragma comment(lib, "ws2_32.lib")
#pragma comment(lib, "cryptlib.lib")

namespace Core
{
	void Initialize();
}