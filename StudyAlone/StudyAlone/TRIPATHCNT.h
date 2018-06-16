#pragma once
#include<cstdio>
#include<cstring>

int triangle[100][100], num[100][100], memoi[100][100];

void init(int n)
{
	memset(num, 0, sizeof(num));
	memset(memoi, 0, sizeof(memoi));

	num[0][0] = 1;

	for (int i = 0; i < n; i++)
	{
		for(int j = 0; j <= i; j++)
		{
			scanf("%d \n", &triangle[i][j]);
		}
	}
}

int max(int i1, int i2)
{
	return i1 < i2 ? i2 : i1;
}

int TRIPATHCNT()
{
	int t,n;
	scanf("%d\n", &t);
	while (t--)
	{
		scanf("%d\n", &n);
		init(n);

		for (int i = 0; i < n - 1; i++)
		{
			for (int j = 0; j <= i; j++)
			{
				int value1 = memoi[i][j] + triangle[i + 1][j], value2 = memoi[i][j] + triangle[i + 1][j + 1];
				if (value1 > memoi[i + 1][j])
				{
					memoi[i + 1][j] = value1;
					num[i + 1][j] = num[i][j];
				}
				else if (value1 == memoi[i + 1][j])
				{
					num[i + 1][j] += num[i][j];
				}

				if (value2 > memoi[i + 1][j + 1])
				{
					memoi[i + 1][j + 1] = value2;
					num[i + 1][j + 1] = num[i][j];
				}
				else if (value2 == memoi[i + 1][j + 1])
				{
					num[i + 1][j + 1] += num[i][j];
				}
			}
		}

		int maxIdx = 0;
		int res = num[n-1][maxIdx];
		for (int i = 1; i < n; i++)
		{
			if (memoi[n - 1][maxIdx] < memoi[n - 1][i])
			{
				maxIdx = i;
				res = num[n - 1][maxIdx];
			}
			else if (memoi[n - 1][maxIdx] == memoi[n - 1][i])
			{
				res += num[n - 1][i];
			}
		}

		printf("%d\n", res);
	}
	return 0;
}