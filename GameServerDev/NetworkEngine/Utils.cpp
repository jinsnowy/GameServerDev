#include "pch.h"
#include "Utils.h"

#include <cryptopp/cryptlib.h>
#include <cryptopp/files.h>
#include <cryptopp/hex.h>
#include <cryptopp/sha.h>
#include <cryptopp/sha3.h>

using namespace CryptoPP;
using CryptoByte = CryptoPP::byte;

std::wstring Utils::WSAGetLastErrorMsg()
{
	return String::ToWide(std::system_category().message(GetLastError()));
}

std::wstring Utils::WSAGetLastErrorMsg(int errCode)
{
	return String::ToWide(std::system_category().message(errCode));
}

std::wstring Utils::GenerateSHA512Hash(const std::wstring& target)
{
	string msg = String::ToNarrow(target);
	string digest;

	SHA3_512 hash;
	hash.Update((const CryptoByte*)msg.data(), msg.size());
	digest.resize(hash.DigestSize());
	hash.Final((CryptoByte*)&digest[0]);

	return String::ToWide(digest);
}

std::wstring Utils::GenerateSHA256Hash(const std::wstring& target)
{
	string msg = String::ToNarrow(target);
	string digest;

	SHA3_256 hash;
	hash.Update((const CryptoByte*)msg.data(), msg.size());
	digest.resize(hash.DigestSize());
	hash.Final((CryptoByte*)&digest[0]);

	return String::ToWide(digest);
}

bool Utils::VerifySHA512Hash(const std::wstring& targetMessage, const std::wstring& givenHash)
{
	string msg = String::ToNarrow(targetMessage);
	string digest = String::ToNarrow(givenHash);

	SHA3_512 hash;
	hash.Update((const CryptoByte*)msg.data(), msg.size());

	return hash.Verify((const CryptoByte*)digest.data());
}

bool Utils::VerifySHA256Hash(const std::wstring& targetMessage, const std::wstring& givenHash)
{
	string msg = String::ToNarrow(targetMessage);
	string digest = String::ToNarrow(givenHash);

	SHA3_256 hash;
	hash.Update((const CryptoByte*)msg.data(), msg.size());

	return hash.Verify((const CryptoByte*)digest.data());
}
