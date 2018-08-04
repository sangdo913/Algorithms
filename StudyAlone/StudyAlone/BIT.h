#pragma once
#include<iostream>
#include<cstdio>

using namespace std;
void Init(int*part_sum,int size)
{
	for (int i = 1; i <= size; i++) part_sum[i] = 0;
}
void PartSumUpdate(int *part_sum, int ind, int value, int size)
{
	while (ind <= size)
	{
		part_sum[ind] += value;
		ind += ind & -ind;
	}
}

int PartSum(int*part_sum, int ind)
{
	int result = 0;
	while (ind)
	{
		result += part_sum[ind];
		ind -= ind&-ind;
	}
	return result;
}
void In(int *arr,int*part_sum, int N)
{
	for (int i = 1; i <= N; i++)
	{
		scanf("%d", arr + i);
		PartSumUpdate(part_sum, i, arr[i], N);
	}
}
void BIT()
{
	typedef int(*BIT_Func)(int* part_sum, int L, int R,int size);
	int T, C, N, M;
	int infos[100001];
	int part_sum[100001];
	BIT_Func funcs[3];
	funcs[1] = [](int* part_sum, int x, int y,int size)->int {PartSumUpdate(part_sum,x,y,size); return 0; };
	funcs[2] = [](int* part_sum, int l, int r, int size)->int {return PartSum(part_sum, r) - PartSum(part_sum, l-1); };
	scanf("%d", &T);
	for (int tc = 1; tc <= T; tc++)
	{
		scanf("%d %d", &N, &M);

		Init(part_sum, N);
		In(infos,part_sum, N);

		printf("#%d", tc);
		int funcP, result,x,y;
		for (int i = 0; i < M; i++)
		{
			scanf("%d %d %d", &funcP,&x,&y);
			result = funcs[funcP](part_sum, x,y,N);
			if (funcP == 2)
			{
				printf(" %d", result);
			}
		}
		printf("\n");
	}
}