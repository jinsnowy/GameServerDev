#pragma once

class StringUtils
{
public:
	static std::string  Format(const char* fmt, ...);
	static std::wstring Format(const wchar_t* fmt, ...);

	static std::wstring ToWide(const std::string& str);
	static std::string  ToNarrow(const std::wstring& str);

	template<typename Iter>
	static std::string Join(Iter first, Iter last, const std::string& delimiter);
	static std::string Join(const std::vector<std::string>& strs, const std::string& delimiter);

	static std::vector<std::string> Split(std::string s, const std::string& delimiter);

	template<size_t sz>
	static void CopyStr(wchar_t(&buffer)[sz], const std::wstring& target)
	{
		if (target.size() > sz) {
			throw std::runtime_error("copy wchar buffer overflows");
		}

		wmemcpy_s(buffer, sz, target.data(), target.size());
	}

	template<size_t sz>
	static void CopyStr(wchar_t(&buffer)[sz], const wchar_t* str)
	{
		size_t len = lstrlenW(str);
		if (len > sz) {
			throw std::runtime_error("copy wchar buffer overflows");
		}

		wmemcpy_s(buffer, sz, str, len);
	}

	template<size_t sz>
	static wstring Slice(const wchar_t(&buffer)[sz], size_t count) {
		return Slice(buffer, 0, count);
	}

	template<size_t sz>
	static wstring Slice(const wchar_t(&buffer)[sz], size_t st, size_t ed) {
		ASSERT_CRASH(st >= 0 && ed <= sz);
		size_t len = ed - st;
		wstring s(len, L'\0');
		wmemcpy_s(s.data(), len, buffer + st, len);

		return s;
	}
};

template<typename Iter>
inline std::string StringUtils::Join(Iter first, Iter last, const std::string& delimiter)
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