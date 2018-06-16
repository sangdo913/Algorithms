#pragma once
#include<cstdio>
#include<cstring>

int adj[50][50]; int n, p;
int deg[50];
double adj2[50][50];
double memoi[101][50];

double dp[101][50];

double probability(int days, int from)
{
	if (days == 0)
	{
		return from == p ? 1.0 : 0.0;
	}

	double& ret = memoi[days][from];

	if (ret > -0.5) return ret;
	
	ret = 0.0;

	for (int i = 0; i < n; i++)
	{
		if (adj[from][i])
			ret += probability(days - 1, i) / deg[i];
	}

	return ret;
}

int NUMB3RS()
{
	int c;

	scanf("%d\n", &c);

	while (c--)
	{
		int d;

		scanf("%d %d %d\n", &n, &d, &p);

		memset(deg, 0, sizeof(deg));

		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < n; j++)
			{
				scanf("%d \n", &adj[i][j]);
				deg[i] += adj[i][j];
			}
		}

		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < n; j++)
			{
				adj2[i][j] = (double)adj[i][j] / deg[i];
			}
		}
/*

		for (int i = 0; i <= d; i++)
		{
			for (int j = 0; j < n; j++)
			{
					memoi[i][j] = -1;
			}
		}
*/
		memset(dp, 0, sizeof(dp));

		dp[0][p] = 1;

		for (int days = 0; days < d; days++)
		{
			for (int i = 0; i < n; i++)
			{
				if (dp[days][i] != 0)
				{
					for (int j = 0; j < n; j++)
					{
						dp[days + 1][j] += dp[days][i] * adj2[i][j];
					}
				}
			}
		}

		int t;
		scanf("%d\n", &t);

		while(t--)
		{
			int q;
			scanf("%d \n", &q);

			printf("%.10lf ", dp[d][q]);
		}

		printf("\n");
	}
	return 0;
}