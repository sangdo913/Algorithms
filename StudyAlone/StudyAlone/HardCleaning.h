#pragma once
// SWEA 극한의 청소 작업 : https://www.swexpertacademy.com/main/talk/codeBattle/problemDetail.do?contestProbId=AWO6cgzKOIEDFAWw&categoryId=AWOuXSOaAEgDFAWw&categoryType=BATTLE
#include<cstdio>

long long fourNum[13] = { 0 };

int getDigit(long long n)
{
	int len = 0;
	while (n)
	{
		len++;
		n /= 10;
	}

	return len;
}

long long abs(long long ll)
{
	return ll > 0 ? ll : -ll;
}

long long getCnt(long long ll, int len, long long sum)
{
	if (len == 0)
	{
		return sum;
	}

	long long digit = 1;

	for (int i = 1; i < len; i++)
	{
		digit *= 10;
	}

	int cnt = ll / digit;

	long long res = 0;
	for (int i = 0; i < cnt; i++)
	{
		if (i == 4)
		{
			res += digit;
			continue;
		}

		res += fourNum[len - 1];
	}

	return getCnt(ll % digit, len - 1, sum + res);
}

int HardCleaning()
{
	long long digit = 1;
	for (int i = 1; i < 13; i++)
	{
		fourNum[i] = fourNum[i - 1] + (fourNum[i - 1] << 3) + digit;
		digit *= 10;
	}

	int t;

	scanf("%d\n", &t);

	for (int tc = 1; tc <= t; tc++)
	{
		long long ll1, ll2;
		scanf("%lld %lld\n", &ll1, &ll2);

		long long res = ll2 - ll1;
		int len1 = getDigit(abs(ll1));
		int len2 = getDigit(abs(ll2));

		res -= getCnt(abs(ll1), len1, 0);
		res -= getCnt(abs(ll2), len2, 0);

		if (ll1 >> 63 ^ ll2 >> 63)
		{
			res = ll2 - ll1 - getCnt(ll2, len2, 0) - getCnt(abs(ll1), len1, 0);
			res--;
		}

		else
		{
			res = ll2 - ll1;
			res -= abs(getCnt(abs(ll1), len1, 0) - getCnt(abs(ll2), len2, 0));
		}

		printf("#%d %lld\n", tc, res);
	}
	return 0;
}