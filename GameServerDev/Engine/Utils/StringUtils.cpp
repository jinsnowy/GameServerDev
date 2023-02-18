#include "pch.h"
#include "StringUtils.h"

std::string StringUtils::Format(const char* fmt, ...)
{
	va_list arg_ptr;
	va_start(arg_ptr, fmt);

	int size = vsnprintf(nullptr, 0, fmt, arg_ptr) + 1;
	if (size <= 1) {
		va_end(arg_ptr);
		return "";
	}

	std::string s(size, '\0');
	vsnprintf(&s[0], size, fmt, arg_ptr);
	s.pop_back();

	va_end(arg_ptr);

	return s;
}

std::wstring StringUtils::Format(const wchar_t* fmt, ...)
{
	wchar_t buffer[1024];

	va_list arg_ptr;
	va_start(arg_ptr, fmt);
	_vsnwprintf_s(buffer, std::size(buffer), fmt, arg_ptr);
	va_end(arg_ptr);

	return buffer;
}

std::wstring StringUtils::ToWide(const std::string& str)
{
	if (str.size() >= DEFAULT_BUF_SIZE)
	{
		wstring wstr;
		wstr.assign(str.begin(), str.end());
		return wstr;
	}

	WCHAR buffer[DEFAULT_BUF_SIZE];
	int length = MultiByteToWideChar(CP_UTF8, 0, str.c_str(), str.size(), buffer, DEFAULT_BUF_SIZE);

	return std::wstring(buffer, length);
}

std::string StringUtils::ToNarrow(const std::wstring& str)
{
	if (str.size() >= DEFAULT_BUF_SIZE)
	{
		string str;
		str.assign(str.begin(), str.end());
		return str;
	}

	CHAR buffer[DEFAULT_BUF_SIZE];
	int length = WideCharToMultiByte(CP_UTF8, 0, str.c_str(), str.size(), buffer, DEFAULT_BUF_SIZE, 0, 0);
	return std::string(buffer, length);
}

std::string StringUtils::Join(const vector<std::string>& strs, const std::string& delimiter)
{
	return Join(strs.begin(), strs.end(), delimiter);
}

std::vector<std::string> StringUtils::Split(std::string s, const std::string& delimiter)
{
	std::vector<std::string> result;

	size_t pos = 0;
	while ((pos = s.find(delimiter)) != std::string::npos) {
		result.push_back(s.substr(0, pos));
		s.erase(0, pos + delimiter.length());
	}

	if (!s.empty()) {
		result.push_back(std::move(s));
	}

	return result;
}
