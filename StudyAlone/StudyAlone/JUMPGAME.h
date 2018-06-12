#pragma once
#include<cstdio>
#include<cstring>

//¿Ü¹ß ¶Ù±â
//¾Ë°í½ºÆÌ
//https://algospot.com/judge/problem/read/JUMPGAME

int canEnd[100][100] = { 0 };
int map[100][100];
int n, c;

bool check(int r, int c)
{
	return r >= 0 && r < n && c >= 0 && c < n;
}

bool follow(int r, int c)
{
	if (r == n - 1 && c == n - 1)
	{
		return true;
	}

	int &ret = canEnd[r][c];

	if (ret == false)
	{
		return false;
	}

	
	if (check(r + map[r][c], c))
	{
		ret = follow(r + map[r][c], c);
		if (ret) return true;
	}

	if (check(r, c + map[r][c]))
	{
		ret = follow(r, c + map[r][c]);
		if (ret) return true;
	}

	return false; 
}

void init()
{
	memset(canEnd, -1, sizeof(canEnd));

	scanf("%d\n", &n);

	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			scanf("%d \n", &map[i][j]);
		}
	}
}

int JUMPGAME()
{
	int t;
	scanf("%d\n", &t);
	const char s[2][4] = { "NO", "YES" };

	while (t--)
	{
		init();
		bool res = follow(0, 0);

		printf("%s\n", s[res]);
	}

	return 0;
}