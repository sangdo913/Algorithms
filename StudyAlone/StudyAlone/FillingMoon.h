#pragma once
#include<iostream>
#include<string.h>
#include<queue>
using namespace std;

struct FillingMoon_Cod
{
	int r,c;
	int inventory;
};

struct FillingMoon_Info
{
	typedef FillingMoon_Cod cod;
	cod st;
	char map[52][52];
	bool visit[1<<('f'-'a'+1)][52][52];
	int n;
	int m;
	const int dx[4] = { 0,0,-1,1 };
	const int dy[4] = { -1,1,0,0 };

	void init()
	{
		memset(visit, false, sizeof(visit));
		scanf("%d %d\n", &n, &m);


		for (int r = 0; r < n + 2; r++)
		{
			for (int c = 0; c < m + 2; c++)
			{
				map[r][c] = '#';
			}
		}


		for (int r = 1; r <= n; r++)
		{
			for (int c = 1; c <= m; c++)
			{
				scanf("%c", &map[r][c]);
				if (map[r][c] == '0')
				{
					st.r = r;
					st.c = c;
					st.inventory = 0;
				}
			}
			scanf("%*[\n]");
		}
	}
	bool CanGo(cod& c)
	{
		if (map[c.r][c.c] == '#') return false;
		else if (map[c.r][c.c] >= 'A' && map[c.r][c.c] <= 'F')
		{
			int keyNum = map[c.r][c.c] - 'A';
			return c.inventory & (1 << keyNum);
		}
		else return true;
	}
	bool isKey(cod &c)
	{
		return (map[c.r][c.c] >= 'a' && map[c.r][c.c] <= 'f');
	}

	void getKey(cod &c)
	{
		c.inventory |= 1 << (map[c.r][c.c] - 'a');
	}
	int Escape()
	{
		queue<cod> que;
		cod pos,next;

		que.push(st);
		int size=1;
		int time = 0;
		while (que.size())
		{
			pos = que.front();
			que.pop();
			if (map[pos.r][pos.c] == '1')
			{
				return time;
			}

			for (int d = 0; d < 4; d++)
			{
				next.r = pos.r + dy[d];
				next.c = pos.c + dx[d];
				next.inventory = pos.inventory;
				if (visit[next.inventory][next.r][next.c]) continue;
				if (CanGo(next))
				{
					visit[next.inventory][next.r][next.c] = true;

					if (isKey(next))
						getKey(next);
					que.push(next);
				}
			}

			size--;
			if (size == 0)
			{
				size = que.size();
				time++;
			}
		}

		return -1;
	}
}FillingMoon_info;

int FillingMoon()
{
	FillingMoon_info.init();
	int res = FillingMoon_info.Escape();
	printf("%d\n", res);
	return 0;
}