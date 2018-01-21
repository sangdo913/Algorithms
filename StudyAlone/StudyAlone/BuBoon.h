#pragma once
#include<iostream>
#include<cstring>
using namespace std;

void BuBoon()
{
	int arr[7];
	bool flag[7];
	int size = 7;

	memset(flag, false, sizeof(flag));

	for (int i = 0; i < (i << size); i++)
	{
		for (int j = 0; j < size; j++)
		{
			if (i & (1 << j)) flag[j] = true;
		}

		//처리(flag 가 true인 애들만)
	}
}
