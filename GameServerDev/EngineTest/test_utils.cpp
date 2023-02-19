#include "pch.h"
#include "Engine/Utils/Crypto.h"

TEST(TestUtils, ����_SHA512�ؽ�_����_�׽�Ʈ) {
	wstring s1(L"asjdoaisjdoiqjwn1=-293i2e=102=401qp;'p'd'12-12[-0ola'lda");
	wstring s2 = s1;

	wstring s1hash = Crypto::GenerateSHA512Hash(s1);
	wstring s2hash = Crypto::GenerateSHA512Hash(s2);
	
	EXPECT_EQ(s1hash, s2hash);
}

TEST(TestUtils, ����_�ٸ�_SHA512�ؽ�_����_�׽�Ʈ) {

	wstring s1(L"asjdoaisjdoiqjwn1=-293i2e=102=401qp;'p'd'12-12[-0ola'lda");
	wstring s2(L"ses;ilejpoiqejfpo;afja;ijsfajd;sja;sdija;sjdaoijsdoajsdi");

	wstring s1hash = Crypto::GenerateSHA512Hash(s1);
	wstring s2hash = Crypto::GenerateSHA512Hash(s2);

	EXPECT_NE(s1hash, s2hash);
}

TEST(TestUtils, SHA512�ؽ�_����_�׽�Ʈ) {
	wstring s1(L"asjdoaisjdoiqjwn1=-293i2e=102=401qp;'p'd'12-12[-0ola'lda");
	wstring s1hash = Crypto::GenerateSHA512Hash(s1);

	EXPECT_TRUE(Crypto::VerifySHA512Hash(s1, s1hash));
}

TEST(TestUtils, ����_�ٸ�_SHA512�ؽ�_����_�׽�Ʈ) {

	wstring s1(L"asjdoaisjdoiqjwn1=-293i2e=102=401qp;'p'd'12-12[-0ola'lda");
	wstring s2(L"ses;ilejpoiqejfpo;afja;ijsfajd;sja;sdija;sjdaoijsdoajsdi");

	wstring s1hash = Crypto::GenerateSHA512Hash(s1);
	wstring s2hash = Crypto::GenerateSHA512Hash(s2);

	EXPECT_FALSE(Crypto::VerifySHA512Hash(s1, s2hash));
	EXPECT_FALSE(Crypto::VerifySHA512Hash(s2, s1hash));
}
