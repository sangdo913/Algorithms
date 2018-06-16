#pragma once
#include<cstdio>

const int INF = 1000000007;
int fibo[101] = { 1, 1};

int TILING2()
{
	int t, n;
	scanf("%d\n", &t);
	for (int i = 2; i <= 100; i++)
	{
		fibo[i] = (fibo[i - 1] + fibo[i - 2]) % INF;
	}

	while (t--)
	{
		scanf("%d\n", &n);
		printf("%d\n", fibo[n]);
	}
	return 0;
}