#pragma once

class SystemUtils
{
public:
	static std::wstring WSAGetLastErrorMsg();
	static std::wstring WSAGetLastErrorMsg(int errCode);

	template<typename T, size_t sz>
	static void Zero(T(&buffer)[sz])
	{
		ZeroMemory(buffer, sizeof(buffer));
	}

	static void Copy(CHAR* dest, size_t dest_size, CHAR* src, size_t src_size) {
		memcpy_s(dest, dest_size, src, src_size);
	}
};