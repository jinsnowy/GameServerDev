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

	size_t szNumberOfConverted = str.size();
	wchar_t buffer[DEFAULT_BUF_SIZE];
	ZeroMemory(&buffer, sizeof(buffer));
	mbstowcs_s(&szNumberOfConverted, buffer, str.c_str(), DEFAULT_BUF_SIZE);

	return buffer;
}

std::string StringUtils::ToNarrow(const std::wstring& str)
{
	if (str.size() >= DEFAULT_BUF_SIZE)
	{
		string str;
		str.assign(str.begin(), str.end());
		return str;
	}

	size_t szNumberOfConverted = str.size();
	CHAR buffer[DEFAULT_BUF_SIZE];
	ZeroMemory(&buffer, sizeof(buffer));
	wcstombs_s(&szNumberOfConverted, buffer, str.c_str(), DEFAULT_BUF_SIZE);

	return buffer;
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
