#pragma once
#ifndef _SINGLETON_H_
#define _SINGLETON_H_

template<typename T>
class ISingleton
{
protected:
	ISingleton() = default;

public:
	virtual ~ISingleton() = default;
	ISingleton(const ISingleton&) = delete;
	ISingleton& operator=(const ISingleton&) = delete;
	ISingleton(ISingleton&&) = delete;
	ISingleton& operator=(ISingleton&&) = delete;

	static T& GetInstance()
	{
		static T instance;
		return instance;
	}
};

#endif // ! _Singleton_H_
