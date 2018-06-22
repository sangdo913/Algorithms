#pragma once
//SWEA
//4534. Æ®¸® Èæ¹é »öÄ¥
//https://www.swexpertacademy.com/main/code/problem/problemDetail.do?contestProbId=AWO6esOKOKQDFAWw&categoryId=AWO6esOKOKQDFAWw&categoryType=CODE
#include<cstdio>
#include<iostream>
#include<vector>
#include<cstring>

using namespace std;

long long nodes[100001][2];
int deg[100001];
int que[100000];
int sta[100000];
vector<int> adj[100001];
int dir[100001];

void init(int n)
{
	memset(deg, 0, sizeof(deg));
	memset(dir, 0, sizeof(dir));

	for (int i = 1; i <= n; i++)
	{
		nodes[i][0] = nodes[i][1] = 1;
		adj[i].clear();
		adj[i].resize(0);
	}
}

int PaintBlackAndWhite()
{
	int t;
	const long long limit = 1000000007;

	scanf("%d\n", &t);

	for (int tc = 1; tc <= t; tc++)
	{
		int n, st, dt;
		int fr = 0, re = 0;

		scanf("%d\n", &n);

		init(n);

		for(int i = 1; i < n; i++)
		{
			scanf("%d %d\n", &st, &dt);
			adj[st].push_back(dt);
			adj[dt].push_back(st);
		}

		int top = 0;
		sta[top++] = 1;

		dir[1] = -1;
		while (top)
		{
			int node = sta[--top];

			for (int i = 0; i < adj[node].size(); i++)
			{
				int next = adj[node][i];

				if (dir[next]) continue;

				sta[top++] = next;
				dir[next] = node;
				deg[node]++;
			}
		}

		for (int i = 1; i <= n; i++)
		{
			if (deg[i] == 0)
			{
				que[re++] = i;
			}
		}

		while (true)
		{
			int node = que[fr++];

			if (node == 1) break;

			int next = dir[node];

			if(--deg[next] == 0)
			{
				que[re++] = next;
			}

			nodes[next][0] *= nodes[node][1] % limit;
			nodes[next][0] %= limit;

			nodes[next][1] *= (nodes[node][0] + nodes[node][1]) % limit;
			nodes[next][1] %= limit;
		}

		printf("#%d %lld\n", tc, (nodes[1][0] + nodes[1][1]) % limit);
	}

	return 0;
}