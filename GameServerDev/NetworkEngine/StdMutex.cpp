#include "pch.h"
#include "StdMutex.h"

size_t StdThreadId::Get()
{
	struct ThreadIdInit
	{
		size_t Id;

		ThreadIdInit()
		{
			static atomic<size_t> IdGen = 1;
			Id = IdGen.fetch_add(1);
		}
	};

	thread_local ThreadIdInit threadId;

	return threadId.Id;
}

const wchar_t* StdThreadIdStr::Get()
{
	struct StdThreadIdStrInit
	{
		wstring IdStr;

		StdThreadIdStrInit()
		{
			wstringstream ss;
			ss << std::this_thread::get_id();
			IdStr = ss.str();
		}
	};

	thread_local StdThreadIdStrInit threadId;

	return threadId.IdStr.c_str();
}
