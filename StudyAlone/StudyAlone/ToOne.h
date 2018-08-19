#pragma once
#include<iostream>
#include"MyHeap.h"

using namespace std;

typedef struct ToOneCOD
{
	long long x;
	long long y;
};

long long double ToOne_GetValue(long long double E, ToOneCOD c1, ToOneCOD c2)
{
	long long double result = E*((c1.x - c2.x)*(c1.x - c2.x) + (c1.y - c2.y)*(c1.y - c2.y));
	return result;
}

ToOneEdge edges[1000000];
ToOneCOD island[1000];
void ToOne()
{
	bool is_visit[1000];
	ios::ios_base::sync_with_stdio(false);
	int T,N;
	long long double E;
	cin >> T;
	for (int tc = 1; tc <= T; tc++)
	{
		Heap pq;
		pq.Init(100000, [](ToOneEdge e1, ToOneEdge e2)->bool {return e1.value < e2.value; });
		for (int i = 0; i < 1000; i++) is_visit[i] = false;
		cin >> N;
		long long cnt = 0;
		for (int i = 0; i < N; i++)
		{
			cin >> island[i].x;
		}
		for (int i = 0; i < N; i++)
		{
			cin >> island[i].y;
		}
		cin >> E;
		for (int i = 0; i < N-1; i++)
			for (int j = i+1; j < N; j++)
			{
				edges[cnt].from = i;
				edges[cnt].to = j;
				edges[cnt++].value = ToOne_GetValue(E, island[i], island[j]);
			}

		for (;cnt--; )
		{
			pq.enque(edges[cnt]);
		}
		cnt = 0;
		long long double result = 0;

		ToOneEdge edge;  pq.deque(edge);

		result += edge.value;
		is_visit[edge.from] = is_visit[edge.to] = true;
		cnt++;

		while (cnt != N - 1)
		{
			pq.deque(edge);
			if (is_visit[edge.from] && is_visit[edge.to]) continue;
			if (!is_visit[edge.from] && !is_visit[edge.to]) continue;

			if (!is_visit[edge.from])
			{
				for (int i = 0; i < N; i++)
				{
					if(!is_visit[i])
						pq.enque({ edge.from,i,ToOne_GetValue(E,island[edge.from],island[i]) });
				}
			}
			else
			{
				for (int i = 0; i < N; i++)
				{
					if (!is_visit[i])
					pq.enque({ edge.to,i,ToOne_GetValue(E,island[edge.to],island[i]) });
				}
			}

			result += edge.value;
			is_visit[edge.from] = is_visit[edge.to] = true;
			cnt++;
		}
		pq.DelHeap();
		cout << '#' << tc << ' ' << (long long)(result+0.5) << endl;
	}
}