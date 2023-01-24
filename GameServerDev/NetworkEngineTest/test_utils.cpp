#include "pch.h"
#include "Utils.h"

TEST(TestUtils, 같은_SHA512해시_생성_테스트) {
	wstring s1(L"asjdoaisjdoiqjwn1=-293i2e=102=401qp;'p'd'12-12[-0ola'lda");
	wstring s2 = s1;

	wstring s1hash = Utils::GenerateSHA512Hash(s1);
	wstring s2hash = Utils::GenerateSHA512Hash(s2);
	
	EXPECT_EQ(s1hash, s2hash);
}

TEST(TestUtils, 서로_다른_SHA512해시_생성_테스트) {

	wstring s1(L"asjdoaisjdoiqjwn1=-293i2e=102=401qp;'p'd'12-12[-0ola'lda");
	wstring s2(L"ses;ilejpoiqejfpo;afja;ijsfajd;sja;sdija;sjdaoijsdoajsdi");

	wstring s1hash = Utils::GenerateSHA512Hash(s1);
	wstring s2hash = Utils::GenerateSHA512Hash(s2);

	EXPECT_NE(s1hash, s2hash);
}

TEST(TestUtils, SHA512해시_검증_테스트) {
	wstring s1(L"asjdoaisjdoiqjwn1=-293i2e=102=401qp;'p'd'12-12[-0ola'lda");
	wstring s1hash = Utils::GenerateSHA512Hash(s1);

	EXPECT_TRUE(Utils::VerifySHA512Hash(s1, s1hash));
}

TEST(TestUtils, 서로_다른_SHA512해시_검증_테스트) {

	wstring s1(L"asjdoaisjdoiqjwn1=-293i2e=102=401qp;'p'd'12-12[-0ola'lda");
	wstring s2(L"ses;ilejpoiqejfpo;afja;ijsfajd;sja;sdija;sjdaoijsdoajsdi");

	wstring s1hash = Utils::GenerateSHA512Hash(s1);
	wstring s2hash = Utils::GenerateSHA512Hash(s2);

	EXPECT_FALSE(Utils::VerifySHA512Hash(s1, s2hash));
	EXPECT_FALSE(Utils::VerifySHA512Hash(s2, s1hash));
}

TEST(TestUtils, 랜덤_스트링_생성)
{
	const int gen_num = 1000;

	unordered_set<wstring> set;
	for (int i = 0; i < gen_num; ++i)
	{
		set.insert(Utils::GenerateRandomString(16));
	}

	EXPECT_EQ(set.size(), gen_num);
}