#pragma once

namespace Core
{
	class Config
	{
	public:
		static std::wstring dbsn;
		static int32 thread_count;
		static uint16 default_port;
		static int64 time_slice_exec;
		static int64 time_slice_io;
		static bool debug_actor_post;
	};
}