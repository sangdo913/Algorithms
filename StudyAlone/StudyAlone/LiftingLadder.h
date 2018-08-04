#pragma once
#include<iostream>
#include<cstring>

using namespace std;

struct Lifting_Info
{
	typedef struct Cod { int r, c; } cod;
	cod canBuild[300];

	int liftCnt;
	bool lift[31][11];
	int num[11];
	int n, m, h;

	void swap(int &a1, int &a2)
	{
		int temp = a1;
		a1 = a2;
		a2 = temp;
		return;
	}

	void init()
	{
		scanf("%d %d %d\n", &n, &m, &h);
		liftCnt = 0;
		memset(lift, false, sizeof(lift));
		int in1, in2;
		while (m--)
		{
			scanf("%d %d\n", &in1, &in2);
			lift[in1][in2] = true;
		}

		for (int r = 1; r <= h; r++)
		{
			for (int c = 1; c < n; c++)
			{
				if (!lift[r][c - 1] && !lift[r][c] && !lift[r][c + 1])
				{
					canBuild[liftCnt].r = r;
					canBuild[liftCnt++].c = c;
				}
			}
		}
	}

	int max(int i1, int i2)
	{
		return i1 > i2 ? i1 : i2;
	}

	int change(int ind, int cnt, int changed)
	{
		int res = -1;

		if (cnt == changed)
		{
			if (ok())
			{
				return cnt;
			}
			else return - 1;
		}

		if (ind == liftCnt) return -1;

		int r = canBuild[ind].r, c = canBuild[ind].c;

		if (!lift[r][c - 1] && !lift[r][c] && !lift[r][c + 1])
		{
			lift[r][c] = true;
			res = change(ind + 1, cnt, changed + 1);
			lift[r][c] = false;
		}

		if (res != -1) return res;

		res = change(ind + 1, cnt, changed);

		return res;
	}

	bool ok()
	{
		for (int i = 1; i <= n; i++)
		{
			num[i] = i;
		}

		for (int i = 1; i <= h; i++)
		{
			for (int j = 1; j < n; j++)
			{
				if (lift[i][j])
				{
					swap(num[j], num[j + 1]);
				}
			}
		}

		for (int i = 1; i <= n; i++)
		{
			if (num[i] != i) return false;
		}

		return true;
	}
}lifintInfo;


int LiftingLadder()
{
	lifintInfo.init();

	int max = lifintInfo.liftCnt > 3 ? 3 : lifintInfo.liftCnt;

	for (int i = 0; i <= max; i++)
	{
		int res = lifintInfo.change(0, i, 0);
		if (res != -1)
		{
			printf("%d\n", res);
			return 0;
		}
	}
	printf("%d\n", -1);
	return 0;
}