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

	static std::wstring GenerateSHA512Hash(const std::wstring& target);
	static std::wstring GenerateSHA256Hash(const std::wstring& target);
	static bool VerifySHA512Hash(const std::wstring& targetMessage, const std::wstring& givenHash);
	static bool VerifySHA256Hash(const std::wstring& targetMessage, const std::wstring& givenHash);

	static std::wstring GenerateRandomString(unsigned int length);
	static void TestDH();
	static void TestGenTime();
};