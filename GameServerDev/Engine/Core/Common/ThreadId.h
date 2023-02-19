#pragma once

class ThreadId
{
private:
	struct Impl
	{
		int id;
		Impl()
		{
			static int id_gen = 0;
			id = ++id_gen;
		}
	};
public:
	static int Get() {
		thread_local Impl id_gen;
		return id_gen.id;
	}
};