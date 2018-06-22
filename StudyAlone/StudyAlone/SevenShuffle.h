#pragma once
#include<cstring>
#include<cstdio>

int m,  order[21][2];
int arrOrder[6000][7];
long long k;
int SevenShuffle()
{
	int t;
	scanf("%d\n", &t);

	for (int tc = 1; tc <= t; tc++)
	{
		scanf("%d %lld\n", &m, &k);

		for (int i = 0; i < 7; i++)
		{
			arrOrder[0][i] = i;
		}

		for (int i = 1; i <= m; i++)
		{
			scanf("%d %d\n", &order[i][0], &order[i][1]);
			
			order[i][0]--;
			order[i][1]--;

			for (int j = 0; j < 7; j++)
				arrOrder[i][j] = arrOrder[i - 1][j];

			arrOrder[i][order[i][0]] = arrOrder[i - 1][order[i][1]];
			arrOrder[i][order[i][1]] = arrOrder[i - 1][order[i][0]];
		}

		int i = m + 1;
		for(; i < 6000; i++)
		{
			for (int j = 0; j < 7; j++)
				arrOrder[i][j] = arrOrder[i - 1][arrOrder[m][j]];

			bool res = true;
			for (int j = 0; j < 7; j++)
			{
				if (arrOrder[i][j] != j)
				{
					res = false;
					break;
				}
			}

			if(res) break;
		}

		long long cnt = (i - m + 1) * m;
		
		k %= cnt;

		for (int i = m + 1; i <= k; i++)
		{
			for (int j = 0; j < 7; j++)
				arrOrder[i][j] = arrOrder[i - 1][j];

			int l = (i - 1) % m + 1;
			arrOrder[i][order[l][0]] = arrOrder[i - 1][order[l][1]];
			arrOrder[i][order[l][1]] = arrOrder[i - 1][order[l][0]];
		}

		printf("#%d ", tc);
		for (int i = 0; i < 7; i++)
		{
			printf("%d", arrOrder[(k)][i]);
		}
		printf("\n");

	}
	return 0;
}