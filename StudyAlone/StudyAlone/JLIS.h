//합친 LIS
//알고스팟
//https://algospot.com/judge/problem/read/JLIS
#pragma once
#include<cstring>
#include<cstdio>

int rLen;
int res[201], n, m;
int arr[2][101] = { 0 };
int lis[102][102];

int max(int i1, int i2)
{
	return i1 > i2 ? i1 : i2;
}

int JLIS(int prev, int idx1, int idx2)
{
	int& ret = lis[idx1][idx2];

	if (ret != -1) return ret;

	int cnt = 1;

	for (int i = idx1; i <= n; i++)
	{
		if (arr[0][i] > prev)
		{
			cnt = max(cnt, 1 + JLIS(arr[0][i], i + 1, idx2));
		}
	}

	for (int i = idx2; i <= m; i++)
	{
		if (arr[1][i] > prev)
		{
			cnt = max(cnt, 1 + JLIS(arr[1][i], idx1, i + 1));
		}
	}

	return ret = cnt;
}


void init()
{
	scanf("%d %d\n", &n, &m);
	memset(lis, -1, sizeof(lis));

	for (int i = 1; i <= n; i++) scanf("%d \n", &arr[0][i]);
	for (int i = 1; i <= m; i++) scanf("%d \n", &arr[1][i]);
}  

int JLIS()
{
	int t;
	scanf("%d\n", &t);
	while (t--)
	{
		init();
		int res = 0;
		
		for (int i = 1; i <= n; i++)
		{
			res = max(res, JLIS(arr[0][i], i + 1, 1));
		}

		for (int i = 1; i <= m; i++)
		{
			res = max(res, JLIS(arr[1][i], 1, i + 1));
		}

		printf("%d\n", res);
	}
	return 0;
}