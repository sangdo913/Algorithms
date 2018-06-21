#pragma once
#include<cstdio>
#include<cstring>

long long k;
int lis[500][500], arr[500];
int len[500], long long nums[500];

int KLIS()
{
	int t;
	scanf("%d\n", &t);

	while (t--)
	{
		int n;
		scanf("%d %lld\n", &n, &k);

		long long max = k + 1;
		for (int i = 0; i < n; i++)
		{
			scanf("%d \n", &arr[i]);


		}
	}

	return 0;
}

