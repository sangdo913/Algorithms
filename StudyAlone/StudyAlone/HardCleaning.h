#pragma once
// SWEA ������ û�� �۾� : https://www.swexpertacademy.com/main/talk/codeBattle/problemDetail.do?contestProbId=AWO6cgzKOIEDFAWw&categoryId=AWOuXSOaAEgDFAWw&categoryType=BATTLE
#include<cstdio>

long long fourNum[13][10] = { 0 };

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

long long abss(long long ll)
{
	return ll > 0 ? ll : -ll;
}

long long getCnt(long long ll, int len, long long digit, long long sum)
{
	if (len == 0)
	{
		return sum;
	}

	int cnt = ll / digit;

	long long res = 0;

	res += fourNum[len][cnt];

	return getCnt(ll % digit, len - 1, digit / 10, sum + res);
}

int HardCleaning()
{
	long long digit = 1;
	for (int i = 1; i < 13; i++)
	{
		fourNum[i][1] = fourNum[i - 1][9] + fourNum[i - 1][1];

		for(int j = 2; j < 10; j++)
		{
			if(j == 5)
			{
				fourNum[i][j] += fourNum[i][j - 1] + digit;
				continue;
			}
			fourNum[i][j] = fourNum[i][j - 1] + fourNum[i][1];
		}

		digit *= 10;
	}

	int t;

	scanf("%d\n", &t);

	for (int tc = 1; tc <= t; tc++)
	{
		long long ll1, ll2;
		scanf("%lld %lld\n", &ll1, &ll2);

		long long res;

		int len1 = getDigit(abss(ll1));
		int len2 = getDigit(abss(ll2));

		long long digit1 = 1, digit2 = 1;

		for (int i = 1; i < len1; i++)
		{
			digit1 *= 10;
		}

		for(int i = 1; i < len2; i++)
		{
			digit2 *= 10;
		}

		if (ll1 >> 63 ^ ll2 >> 63)
		{
			res = ll2 - ll1 - getCnt(ll2, len2, digit2, 0) - getCnt(abss(ll1), len1, digit1, 0);
			res--;
		}

		else
		{
			res = ll2 - ll1;
			res -= abss(getCnt(abss(ll1), len1, digit1, 0) - getCnt(abss(ll2), len2, digit2, 0));
		}

		printf("#%d %lld\n", tc, res);
	}
	return 0;
}