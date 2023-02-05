#pragma once

#include <typeinfo>
#include "StringUtils.h"

class Reflection
{
public:
	template <typename T>
	struct TypeInfo
	{
		const char* name;
		std::string name_str;
		std::wstring name_str_w;

		TypeInfo()
		{
			name = typeid(T).name();
			name_str = name;
			name_str_w = StringUtils::ToWide(name_str);
		}

		NO_COPY_AND_ASSIGN(TypeInfo<T>);
	};

public:
	template<typename T>
	static TypeInfo<T>& GetTypeInfo()
	{
		static TypeInfo<T> typeInfo;
		return typeInfo;
	}
};

