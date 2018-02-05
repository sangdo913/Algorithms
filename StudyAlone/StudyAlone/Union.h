#pragma once
#include<iostream>
#include<cstdio>

using namespace std;

unsigned int arrays[1000001];

typedef unsigned int(*FUNC[2])(unsigned int* arr, unsigned int factor1, unsigned int factor2);
unsigned int Union_find_parent(unsigned int* arr, unsigned int factor1)
{
	unsigned int temp = factor1;
	while (temp != arr[temp])
	{
		arr[temp] = arr[arr[temp]];
		temp = arr[temp];
	}
	arr[factor1] = temp;
	return temp;
}
unsigned int Union_union(unsigned int*arr, unsigned int factor1, unsigned int factor2)
{
	arr[Union_find_parent(arr, factor1)] = Union_find_parent(arr, factor2);
	return 1;
}
unsigned int Union_IsSame(unsigned int *arr, unsigned int factor1, unsigned int factor2)
{
	return Union_find_parent(arr,factor1) == Union_find_parent(arr,factor2);
}
void Union()
{
	FUNC func;
	unsigned int T, N, M;
	func[0] = Union_union;
	func[1] = Union_IsSame;
	scanf("%d", &T);
	for (int tc = 1; tc <= T; tc++)
	{
		scanf("%d %d", &N,&M);
		for (unsigned int i = 0; i <= N; i++)
		{
			arrays[i] = i;
		}
		unsigned int funcnt, factor1, factor2;
		printf("#%d ", tc);
		for (unsigned int j = 0; j < M; j++)
		{
			scanf("%d %d %d", &funcnt, &factor1, &factor2);
			unsigned int result = func[funcnt](arrays, factor1, factor2);
			if (funcnt)printf("%d",result);
		}
		printf("\n");
	}
}