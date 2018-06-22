#pragma once
#include<cstdio>

int fibo[101] = { 1, 1 };
int sync[101] = {1, 1};

const int INF = 1000000007;

int ASYMTILING()
{
	int t;

	for (int i = 2; i <= 100; i++)
	{
		fibo[i] = (fibo[i - 1] + fibo[i - 2]) % INF;
		sync[i] = i & 1 ? fibo[(i - 1) / 2] : (fibo[i/2] + fibo[i/2 - 1]) % INF;
	}

	scanf("%d\n", &t);

	while (t--)
	{
		int n;
		scanf("%d\n", &n);

		printf("%d\n", (INF + fibo[n] - sync[n])%INF);
	}
	return 0;
}
