#pragma once
#include<cstdio>
#include<cstring>

int cache[101][1001];
char names[101][21];
int n, w;
int info[101][2];

char* res[100]; int rLen;

enum DATA  { V,W };

int getMax(int i1, int i2)
{
	return i1 < i2 ? i2 : i1;
}

int choose2(int now, int v)
{
	if (now > n)
	{
		return 0;
	}

	int& ret = cache[now][v];
	
	if (ret != -1) return ret;

	ret = choose2(now + 1, v);
	if( v + info [now][V] <= w)
		ret = getMax(ret, info[now][W] + choose2(now + 1, v + info[now][V]));

	return ret;
}

void setRes(int start, int v)
{
	if (start > n)
	{
		return;
	}

	if (choose2(start, v) == choose2(start + 1, v))
	{
		setRes(start + 1, v);
	}

	else
	{
		res[rLen++] = names[start];
		setRes(start + 1, v + info[start][V]);
	}
}

int PACKING()
{
	int t;
	scanf("%d\n", &t);

	while (t--)
	{
		scanf("%d %d\n", &n, &w);
		memset(cache, -1, sizeof(cache));

		for (int i = 1; i <= n; i++)
		{
			scanf("%s %d %d\n", names[i], &info[i][V], &info[i][W]);
		}

		int maxW = choose2(0, 0);
		rLen = 0;
		setRes(0, 0);

		int idx = 0;
		printf("%d %d\n", maxW, rLen);

		for (int i = 0; i < rLen; i++) printf("%s\n", res[i]);
	}
	return 0;
}