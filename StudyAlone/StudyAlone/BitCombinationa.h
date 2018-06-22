#pragma once
#include<cstdio>

int num[15];

int getZeros(int n)
{
	int num = 0;
	while ((n & 1) == 0)
	{
		num++;
		n >>= 1;
	}

	return num;
}

void func(int bit, int n)
{
	int msb = 1 << (n - 1);
	while (msb)
	{
		printf("%d ", (bool)(msb & bit));
		msb >>= 1;
	}
	printf("\n");
}

int BitCombination()
{
	int bit;
	int n, m;

	scanf("%d %d\n", &n, &m);

	for (int i = 0; i < n; i++)
	{
		scanf("%d \n", num + i);
	}

	bit = (1 << m) - 1;

	while (bit < (1 << n))
	{
		func(bit, n);
		int temp = bit | ((bit & -bit) - 1);

		bit = (temp + 1) | (((~temp & -~temp) - 1) >> (getZeros(bit) + 1));
	}

	return 0;
}