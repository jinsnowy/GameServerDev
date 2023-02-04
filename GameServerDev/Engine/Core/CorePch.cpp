#include "pch.h"

#include "Core/Memory/MemoryPool.h"
#include "Utils/Utils.h"

void Core::Initialize()
{
	MemoryPool::Initialize();
	NetUtils::Initialize();
}
