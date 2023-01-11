#pragma once

#include <string>
#include <vector>

class String
{
public:
	static std::string Format(const char* fmt, ...);

	static std::wstring ToWide(const std::string& str);
	static std::string ToNarrow(const std::wstring& str);

	template<typename Iter>
	static std::string Join(Iter first, Iter last, const std::string& delimiter);
	static std::string Join(const std::vector<std::string>& strs, const std::string& delimiter);

	static std::vector<std::string> Split(std::string s, const std::string& delimiter);
};

template<typename Iter>
inline std::string String::Join(Iter first, Iter last, const std::string& delimiter)
{
	auto iter = first;
	std::stringstream ss;
	for (; iter != last;)
	{
		ss << *iter; ++iter;
		if (iter != last)
			ss << delimiter;
	}

	return ss.str();
}