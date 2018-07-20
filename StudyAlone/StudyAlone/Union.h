#pragma once
#include<iostream>
#include<cstdio>

using namespace std;

long long arrays[1000001];

typedef long long(*FUNC[2])(long long* arr, long long factor1, long long factor2);
long long Union_find_parent(long long* arr, long long factor1)
{
	long long temp = factor1;
	while (temp != arr[temp])
	{
		arr[temp] = arr[arr[temp]];
		temp = arr[temp];
	}
	arr[factor1] = temp;
	return temp;
}
long long Union_union(long long*arr, long long factor1, long long factor2)
{
	arr[Union_find_parent(arr, factor1)] = Union_find_parent(arr, factor2);
	return 1;
}
long long Union_IsSame(long long *arr, long long factor1, long long factor2)
{
	return Union_find_parent(arr,factor1) == Union_find_parent(arr,factor2);
}
void Union()
{
	FUNC func;
	long long T, N, M;
	func[0] = Union_union;
	func[1] = Union_IsSame;
	scanf("%d", &T);
	for (int tc = 1; tc <= T; tc++)
	{
		scanf("%d %d", &N,&M);
		for (long long i = 0; i <= N; i++)
		{
			arrays[i] = i;
		}
		long long funcnt, factor1, factor2;
		printf("#%d ", tc);
		for (long long j = 0; j < M; j++)
		{
			scanf("%d %d %d", &funcnt, &factor1, &factor2);
			long long result = func[funcnt](arrays, factor1, factor2);
			if (funcnt)printf("%d",result);
		}
		printf("\n");
	}
}