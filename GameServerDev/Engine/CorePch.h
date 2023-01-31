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

#include "Stl.h"

using namespace std;

#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <mswsock.h>
#include <rpc.h>

#include "CoreMacro.h"
#include "CoreDefine.h"
#include "CoreStruct.h"

#include "TlsMemory.h"
#include "Singleton.h"
#include "Logger.h"

#include "Common.h"
#include "IoEvent.h"
#include "MemoryPool.h"
#include "Task.h"
#include "TaskAsync.h"
#include "Alarm.h"

#pragma comment(lib, "Rpcrt4.lib")
#pragma comment(lib, "ws2_32.lib")
#pragma comment(lib, "cryptlib.lib")
