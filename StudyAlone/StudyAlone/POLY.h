#pragma once
#include<cstdio>
#include<cstring>

int poly[101][101] = { 0 };
const int MOD = 10000000;

int getPOLY(int nums, int down)
{
	int& ret = poly[nums][down];

	if (nums == down)
	{
		return ret = 1;
	}

	if (ret != -1) return ret;

	ret = 0;

	int blocks = nums - down;
	for (int i = 1; i <= blocks; i++)
	{
		ret += (i + down - 1) * getPOLY(blocks, i);
		ret %= MOD;
	}

	return ret;
}

int POLY()
{
	int t;
	scanf("%d\n", &t);

	while (t--)
	{
		int n;
		scanf("%d\n", &n);

		memset(poly, -1, sizeof(poly));

		int res = 0;
		for (int i = 1; i <= n; i++)
		{
			res += getPOLY(n, i);
			res %= MOD;
		}

		printf("%d\n", res);
	}

	return 0;
}