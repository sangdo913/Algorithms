#pragma once
#include<iostream>
#include<stack>
#include<queue>
#include<string.h>

using namespace std;

struct Balelino_Cod
{
	int r;
	int c;
	bool operator==(Balelino_Cod c2)
	{
		return r == c2.r && c == c2.c;
	}
};

struct Balelino_Info
{
	typedef Balelino_Cod cod;
	int n;
	int m;
	cod st, dt;
	int map[34][34];
	bool reserved[34][34];
	bool visit[34][34];
	long long memoi[34][34];
	int num[34][34];
	long long min;
	int dx[8] = { 1,   2,2,1,-1,-2,-2,-1 };
	int dy[8] = { -2, -1,1,2, 2, 1,-1,-2 };
	void init()
	{
		memset(map, -1, sizeof(map));
		memset(reserved, false, sizeof(reserved));
		memset(memoi, 0, sizeof(memoi));
		memset(visit, false, sizeof(visit));
		memset(num, -1, sizeof(num));
		min = INT64_MAX;
		scanf("%d %d", &n, &m);
		st = { 0,0 };
		for (int r = 2; r < n + 2; r++)
		{
			for (int c = 2; c < m + 2; c++)
			{
				scanf("%d", &map[r][c]);
				if (map[r][c] == 3) st = { r,c};
				else if (map[r][c] == 4) dt = { r,c };
				else if (map[r][c] == 2) map[r][c] = -1;
			}
		}

		reserved[st.r][st.c] = true;
	}
	long long result()
	{
		return memoi[dt.r][dt.c];
	}
	void Dance()
	{
		queue<cod> q;
		cod next, now;
		q.push(st);
		memoi[st.r][st.c] = 1;
		num[st.r][st.c] = 0;
		while (q.size())
		{
			now = q.front();
			q.pop();
			for (int d = 0; d < 8; d++)
			{
				next.r = now.r + dy[d];
				next.c = now.c + dx[d];
				if (num[next.r][next.c] > min) continue;
				if (map[next.r][next.c] == -1) continue;

				if ((num[next.r][next.c] == -1) || ( num[next.r][next.c] == (num[now.r][now.c] + (map[next.r][next.c] == 0))))
				{
					num[next.r][next.c] = num[now.r][now.c] + (map[next.r][next.c] == 0);
					memoi[next.r][next.c] += memoi[now.r][now.c];
				}

				else if (num[next.r][next.c] > num[now.r][now.c] + (map[next.r][next.c] == 0))
				{
					num[next.r][next.c] = num[now.r][now.c] + (map[next.r][next.c] == 0);
					memoi[next.r][next.c] = memoi[now.r][now.c];
				}
				else
				{
					continue;
				}


				if (next == dt)
				{
					if (min > num[next.r][next.c])
					{
						min = num[next.r][next.c];
					}
					continue;
				}

				q.push(next);
			}

			memoi[now.r][now.c] = 0;

		}

	}

}Balelino_info;

int Balelino()
{
	Balelino_info.init();
	Balelino_info.Dance();
	printf("%lld\n", (Balelino_info.min == INT64_MAX ? -1 : Balelino_info.min));
	if (Balelino_info.min != INT64_MAX) printf("%lld\n", Balelino_info.result());

	return 0;
}