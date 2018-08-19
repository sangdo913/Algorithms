#pragma once
#include<cstdio>
#include<cstring>

long long double memoi[1001][1001];

int n, m;

long long double climb(int days, int h)
{

	long long double& ret = memoi[days][h];

	if (h >= n)
	{
		return ret = 1;
	}

	if (days == m)
	{
		return ret = h >= n;
	}


	if (ret != -1) return ret;

	return ret = 0.75* climb(days + 1, h + 2) + 0.25 * climb(days + 1, h + 1);
}

int SNAIL()
{
	int t;
	scanf("%d\n", &t);
	
	while (t--)
	{
		scanf("%d %d\n", &n, &m);

		for (int i = 0; i <= m; i++)
		{
			for (int j = 0; j <= n; j++)
			{
				memoi[i][j] = -1;
			}
		}

		long long double res = climb(0, 0);

		printf("%.10lf\n", res);
	}

	return 0;
}