#pragma once
#ifndef _THREAD_STATIC_SINGLETON_H_
#define _THREAD_STATIC_SINGLETON_H_

template<typename T>
class IThreadStaticSingleton
{
protected:
	IThreadStaticSingleton() = default;

public:
	virtual ~IThreadStaticSingleton() = default;
	IThreadStaticSingleton(const IThreadStaticSingleton&) = delete;
	IThreadStaticSingleton& operator=(const IThreadStaticSingleton&) = delete;
	IThreadStaticSingleton(IThreadStaticSingleton&&) = delete;
	IThreadStaticSingleton& operator=(IThreadStaticSingleton&&) = delete;

	static T& GetInstance()
	{
		thread_local T instance;
		return instance;
	}
};

#endif // ! _THREAD_STATIC_SINGLETON_H_
