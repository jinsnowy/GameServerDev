#include "pch.h"

#include "Core/System/Memory/MemoryPool.h"
#include "Utils/Utils.h"

void Core::Initialize()
{
	System::Memory::MemoryPool::Initialize();
	NetUtils::Initialize();
}
