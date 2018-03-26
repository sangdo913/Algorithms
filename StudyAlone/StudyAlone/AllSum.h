#pragma once
#include<iostream>

using namespace std;

int AllSum_memoi[10][10];

long long AllSum_DigitSum(long long num)
{
	long long res = 0;
	while(num)
	{
		res = AllSum_memoi[res][num % 10];
		num /= (long long)10;
	}
	return res;
}

int AllSum()
{
	int T;
	long long num;
	scanf("%d", &T);
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			AllSum_memoi[i][j] = ((i + j) % 10) + (i+j)/10;
		}
	}
	for (int tc = 1; tc <= T; tc++)
	{
		scanf("%lld", &num);
		num = AllSum_DigitSum(num);
		printf("#%d %lld\n", tc, num);
	}

	return 0;
}