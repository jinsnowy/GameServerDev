#pragma once

class Utils
{
public:







	template<typename T>
	static shared_ptr<T> SharedGlobal()
	{
		static shared_ptr<T> inst = make_shared<T>();

		return inst;
	}
};