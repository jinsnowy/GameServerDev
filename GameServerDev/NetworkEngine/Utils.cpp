#include "pch.h"
#include "Utils.h"

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

std::wstring Utils::GenerateRandomString(unsigned int length)
{
	// Scratch Area
	SecByteBlock scratch(length);

	// Construction
	CryptoPP::AutoSeededRandomPool rng;

	// Random Block
	rng.GenerateBlock(scratch, scratch.size());

	wstringstream wss;
	wss << scratch;

	return wss.str();
}

void Utils::TestDH()
{
	AutoSeededRandomPool rnd;
	unsigned int bits = 1024;

	try
	{
		cout << "Generating prime of size " << bits << " and generator" << endl;

		// Safe primes are of the form p = 2q + 1, p and q prime.
		// These parameters do not state a maximum security level based
		// on the prime subgroup order. In essence, we get the maximum
		// security level. There is no free lunch: it means more modular
		// mutliplications are performed, which affects performance.

		// For a compare/contrast of meeting a security level, see dh-init.zip.
		// Also see http://www.cryptopp.com/wiki/Diffie-Hellman and
		// http://www.cryptopp.com/wiki/Security_level .

		// CryptoPP::DL_GroupParameters_IntegerBased::GenerateRandom (gfpcrypt.cpp)
		// CryptoPP::PrimeAndGenerator::Generate (nbtheory.cpp)
		DH dh;
		dh.AccessGroupParameters().GenerateRandomWithKeySize(rnd, bits);

		if (!dh.GetGroupParameters().ValidateGroup(rnd, 3))
			throw runtime_error("Failed to validate prime and generator");

		size_t count = 0;

		const Integer& p = dh.GetGroupParameters().GetModulus();
		count = p.BitCount();
		cout << "P (" << std::dec << count << "): " << std::hex << p << endl;

		const Integer& q = dh.GetGroupParameters().GetSubgroupOrder();
		count = q.BitCount();
		cout << "Q (" << std::dec << count << "): " << std::hex << q << endl;

		const Integer& g = dh.GetGroupParameters().GetGenerator();
		count = g.BitCount();
		cout << "G (" << std::dec << count << "): " << std::dec << g << endl;

		// http://groups.google.com/group/sci.crypt/browse_thread/thread/7dc7eeb04a09f0ce
		Integer v = ModularExponentiation(g, q, p);
		if (v != Integer::One())
			throw runtime_error("Failed to verify order of the subgroup");
	}
	catch (const CryptoPP::Exception& e)
	{
		cerr << e.what() << endl;
	}
	catch (const std::exception& e)
	{
		cerr << e.what() << endl;
	}

	AutoSeededRandomPool prng;
	Integer p, q, g;
	PrimeAndGenerator pg;

	pg.Generate(1, prng, 512, 511);
	p = pg.Prime();
	q = pg.SubPrime();
	g = pg.Generator();

	DH dh(p, q, g);
	SecByteBlock t1(dh.PrivateKeyLength()), t2(dh.PublicKeyLength());
	dh.GenerateKeyPair(prng, t1, t2);
	Integer k1(t1, t1.size()), k2(t2, t2.size());


	cout << "Private key:\n";
	cout << hex << k1 << endl;
	cout << "Public key:\n";
	cout << hex << k2 << endl;
}

void Utils::TestGenTime()
{
	try 
	{
		int bits = 2048;

		AutoSeededRandomPool prng;
		RSA::PrivateKey rsa;
		ThreadUserTimer timer(TimerBase::MILLISECONDS);

		timer.StartTimer();

		rsa.GenerateRandomWithKeySize(prng, bits);

		unsigned long elapsed = timer.GetCurrentTimerValue();
		unsigned long ticks = timer.TicksPerSecond();
		unsigned long seconds = elapsed / ticks;

		// days, hours, minutes, seconds, 100th seconds
		unsigned int d = 0, h = 0, m = 0, s = 0, p = 0;

		p = ((elapsed * 100) / ticks) % 100;
		s = seconds % 60;
		m = (seconds / 60) % 60;
		h = (seconds / 60 / 60) % 60;
		d = (seconds / 60 / 60 / 24) % 24;

		float fs = (seconds + ((float)p / 100));

		stringstream ss;

		if (d) {
			ss << d << ((d == 1) ? " day, " : " days, ");
			goto print_hours;
		}

		if (h) {
		print_hours:
			ss << h << ((h == 1) ? " hour, " : " hours, ");
			goto print_minutes;
		}

		if (m) {
		print_minutes:
			ss << m << ((m == 1) ? " minute, " : " minutes, ");
		}

		ss << s << ((s == 1) ? " second" : " seconds");

		cout << "Elapsed time for " << bits << " RSA key: ";
		cout << fixed << setprecision(2) << fs << "s";
		if (seconds)
			cout << " (" << ss.str() << ")";
		cout << endl;
	}
	catch (CryptoPP::Exception& e)
	{
		cerr << e.what() << endl;
	}
	catch (std::exception& e)
	{
		cerr << e.what() << endl;
	}
}