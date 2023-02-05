#include "pch.h"
#include "Crypto.h"

#include <cryptopp/cryptlib.h>
#include <cryptopp/files.h>
#include <cryptopp/hex.h>
#include <cryptopp/sha.h>
#include <cryptopp/sha3.h>
#include <cryptopp/osrng.h>
#include <cryptopp/nbtheory.h>
#include <cryptopp/dh.h>
#include <cryptopp/secblock.h>
#include <cryptopp/hrtimer.h>
#include <cryptopp/rsa.h>

using namespace CryptoPP;
using CryptoByte = CryptoPP::byte;

static auto& RandomEngine() {
	thread_local CryptoPP::AutoSeededRandomPool rng;
	rng.Reseed(true);
	return rng;
}

std::wstring Crypto::GenerateUUID()
{
	wstring out;
	UUID uuid;
	UuidCreate(&uuid);

	wchar_t* str;
	UuidToStringW(&uuid, (RPC_WSTR*)&str);

	size_t len = lstrlenW(str);
	out.resize(len);
	wmemcpy(out.data(), str, len);

	RpcStringFreeW((RPC_WSTR*)&str);

	return out;
}

std::wstring Crypto::GenerateSHA512Hash(const std::wstring& target)
{
	string msg = StringUtils::ToNarrow(target);
	string digest;

	SHA3_512 hash;
	hash.Update((const CryptoByte*)msg.data(), msg.size());
	digest.resize(hash.DigestSize());
	hash.Final((CryptoByte*)&digest[0]);

	return StringUtils::ToWide(digest);
}

std::wstring Crypto::GenerateSHA256Hash(const std::wstring& target)
{
	string msg = StringUtils::ToNarrow(target);
	string digest;

	SHA3_256 hash;
	hash.Update((const CryptoByte*)msg.data(), msg.size());
	digest.resize(hash.DigestSize());
	hash.Final((CryptoByte*)&digest[0]);

	return StringUtils::ToWide(digest);
}

bool Crypto::VerifySHA512Hash(const std::wstring& targetMessage, const std::wstring& givenHash)
{
	string msg = StringUtils::ToNarrow(targetMessage);
	string digest = StringUtils::ToNarrow(givenHash);

	SHA3_512 hash;
	hash.Update((const CryptoByte*)msg.data(), msg.size());

	return hash.Verify((const CryptoByte*)digest.data());
}

bool Crypto::VerifySHA256Hash(const std::wstring& targetMessage, const std::wstring& givenHash)
{
	string msg = StringUtils::ToNarrow(targetMessage);
	string digest = StringUtils::ToNarrow(givenHash);

	SHA3_256 hash;
	hash.Update((const CryptoByte*)msg.data(), msg.size());

	return hash.Verify((const CryptoByte*)digest.data());
}