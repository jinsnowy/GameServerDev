#pragma once

class repositoy_exception : public std::exception
{
private:
	std::string _buffer;
	std::wstring _buffer_w;

public:
	repositoy_exception(const char* reason);
	
	const char* what() const { return _buffer.c_str(); }

	const wchar_t* what_t() const { return _buffer_w.c_str(); }
};

