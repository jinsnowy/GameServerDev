#pragma once

#include "../ThirdParty/MagicEnum/magic_enum.hpp"

class Enums
{
public:
	template <typename E> requires std::is_enum_v<E>
	static auto Count() 
	{
		return magic_enum::enum_count<E>();
	}

	template <typename E> requires std::is_enum_v<E>
	static auto Values()
	{
		return magic_enum::enum_values<E>();
	}

	template <typename E> requires std::is_enum_v<E>
	static auto Names()
	{
		return magic_enum::enum_names<E>();
	}
};