#pragma once

class Utils
{
public:
	static std::wstring WSAGetLastErrorMsg();
	static std::wstring WSAGetLastErrorMsg(int errCode);

	template<typename T>
	static shared_ptr<T> SharedGlobal()
	{
		static shared_ptr<T> inst = make_shared<T>();

		return inst;
	}

	static std::wstring GenerateUUID();

	static std::wstring GenerateSHA512Hash(const std::wstring& target);
	static std::wstring GenerateSHA256Hash(const std::wstring& target);
	static bool VerifySHA512Hash(const std::wstring& targetMessage, const std::wstring& givenHash);
	static bool VerifySHA256Hash(const std::wstring& targetMessage, const std::wstring& givenHash);

	static std::wstring GenerateRandomString(unsigned int length);
	static void TestDH();
	static void TestGenTime();

	template<size_t sz>
	static void CopyStr(wchar_t (&buffer)[sz], const std::wstring& target)
	{
		if (target.size() > sz) {
			throw std::runtime_error("copy wchar buffer overflows");
		}

		wmemcpy_s(buffer, sz, target.data(), target.size());
	}

	template<size_t sz>
	static void CopyStr(wchar_t (&buffer)[sz], const wchar_t* str)
	{
		size_t len = lstrlenW(str);
		if (len > sz) {
			throw std::runtime_error("copy wchar buffer overflows");
		}

		wmemcpy_s(buffer, sz, str, len);
	}

	template<size_t sz>
	static void Init(wchar_t(&buffer)[sz])
	{
		ZeroMemory(buffer, sizeof(buffer));
	}

	template<size_t sz>
	static void Init(char(&buffer)[sz])
	{
		ZeroMemory(buffer, sizeof(buffer));
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