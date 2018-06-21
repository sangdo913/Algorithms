#pragma once
#include<cstdio>

int ndiv[100001] = { 0 };
int max[100001];

int MaxNumOfDivisor()
{
	int tc;
	scanf("%d\n", &tc);
	ndiv[1] = 1;
	max[1] = 1;

	for (int i = 2; i <= 100000; i++)
	{
		int j;
		for (j = 2; j*j < i; j++)
		{
			ndiv[i] = (i % j) == 0 ? ndiv[i] + 2 : ndiv[i];
		}

		ndiv[i] += 2 + (j*j == i);
		max[i] = ndiv[i] >= ndiv[max[i-1]] ? i : max[i-1];
	}

	for (int t = 1; t <= tc; t++)
	{
		int n;
		scanf("%d\n", &n);
		printf("#%d %d\n", t, max[n]);
	}
	return 0;
}
