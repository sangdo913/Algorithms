#pragma once
#include<cstdio>
#include<cstring>

int queue[200], adj[100][2], visit[100] = { 0 }, alen[100] = { 0 };
int fr, re;

int FindPath()
{
	for (int tc = 1; tc <= 10; tc++)
	{
		int tn, n;
		memset(adj, -1, sizeof(adj));
		memset(alen, 0, sizeof(alen));

		scanf("%d %d\n", &tn, &n);

		while (n--)
		{
			int from, to;
			scanf("%d %d \n", &from, &to);
			adj[from][alen[from]++] = to;
		}

		int st = 0;
		re = fr = 0;

		for (int i = 0; i < alen[0]; i++) queue[re++] = adj[0][i];

		visit[0] = tc;

		bool isEnd = false;
		
		while (re != fr)
		{
			int now = queue[fr++];
			if (now == 99)
			{
				isEnd = true;
				break;
			}

			for (int i = 0; i < alen[now]; i++)
			{
				int next = adj[now][i];
				if (visit[next] == tc) continue;
				visit[next] = tc;

				queue[re++] = adj[now][i];
			}
		}

		printf("#%d %d\n", tc, isEnd);
	}
	return 0;
}