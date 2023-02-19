#pragma once

template <typename T>
class Builder
{
public:
	T& self() 
	{
		return *static_cast<T*>(this);
	}
};