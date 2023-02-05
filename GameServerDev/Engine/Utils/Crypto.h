#pragma once

class Crypto
{
public:
	static std::wstring GenerateUUID();
	static std::wstring GenerateSHA512Hash(const std::wstring& target);
	static std::wstring GenerateSHA256Hash(const std::wstring& target);

	static bool VerifySHA512Hash(const std::wstring& targetMessage, const std::wstring& givenHash);
	static bool VerifySHA256Hash(const std::wstring& targetMessage, const std::wstring& givenHash);
};

