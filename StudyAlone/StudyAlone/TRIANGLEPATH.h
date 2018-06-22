#pragma once
#include<cstdio>
#include<cstring>

int triangle[101][101];
int memoi[101][102], n;

int max(int i1, int i2)
{
	return i1 > i2 ? i1 : i2;
}

void init()
{
	scanf("%d\n", &n);

	memset(memoi, 0, sizeof(memoi));

	for (int i = 1; i <= n; i++)
	{
		for (int j = 1; j <= i; j++)
		{
			scanf("%d\n", &triangle[i][j]);
			memoi[i][j] += triangle[i][j];
			memoi[i + 1][j] = max(memoi[i][j], memoi[i + 1][j]);
			memoi[i + 1][j + 1] = max(memoi[i][j], memoi[i + 1][j + 1]);
		}
	}
}

int TRIANGLEPATH()
{
	int t;
	scanf("%d\n", &t);

	while (t--)
	{
		init();

		int res = memoi[n][1];
		for (int i = 2; i <= n; i++)
		{
			res = max(res, memoi[n][i]);
		}
		printf("%d\n", res);
	}
	return 0;
}