#pragma once
#include<iostream>
#include<vector>
#include<algorithm>
#include<queue>
using namespace std;

struct Balabong_Edge
{
	int from;
	int to;
	long long dist;
	long long memoi;
};


bool operator <(Balabong_Edge b1, Balabong_Edge b2)
{
	return b1.dist > b2.dist;
}
vector<int> Balabong_road;
long long Balabong_roadMax[100000];
long long Balabong_roadMax2[100000];
long long Balabong_roadValue[100000];
vector<Balabong_Edge>Balabong_adj [100000];
int Balabong_outDegree[100000];
bool Balabong_visit[100000];
int Balabong_roadNum[100001];
int Balabong_prev[100000];
int Balabong_prev2[100000];
long long Balabong_min(long long l1, long long l2)
{
	return l1 > l2 ? l2 : l1;
}

long long Balabong_max(long long l1, long long l2)
{
	return l1 < l2 ? l2 : l1;
}

long long Balabong_MakeMaxDistance(int roadNum,int ind, int now,long long prevMax)
{
	int prev;
	long long length = prevMax + Balabong_roadMax[ind];
	Balabong_roadValue[roadNum] = Balabong_max(Balabong_roadMax[ind], prevMax);
	long long dist, reverseDist;
	prev = Balabong_prev[ind];
	while (prev != -1)
	{
		dist = Balabong_max(Balabong_roadMax[prev], length - Balabong_roadMax[prev]);
		Balabong_roadValue[roadNum] = Balabong_min(Balabong_roadValue[roadNum], dist);
		prev = Balabong_prev[prev];
	}

	prev = now;
	while (prev != -1)
	{
		dist = Balabong_max(Balabong_roadMax[prev], length - Balabong_roadMax[prev]);
		Balabong_roadValue[roadNum] = Balabong_min(Balabong_roadValue[roadNum], dist);
		prev = Balabong_prev[prev];
	}
	return length;
}

int BalabongStory()
{
	int T, M, L, N,from, to;
	typedef Balabong_Edge Edge;
	long long res,dist;
	Edge edge;
	scanf("%d", &T);
	for (int tc = 1; tc <= T; tc++)
	{
		//init
		scanf("%d %d %d", &N, &M, &L);

		priority_queue<Balabong_Edge> pq;

		Balabong_road.clear();
		for (int i = 0; i < N; i++)
		{
			Balabong_visit[i] = false;
			Balabong_roadMax[i] = 0;
			Balabong_roadMax2[i] = 0;
			Balabong_outDegree[i] = 0;
			Balabong_roadNum[i] = -1;
			Balabong_adj[i].clear();
			Balabong_roadValue[i] = 1000000000000;
			Balabong_prev[i] = -1;
			Balabong_prev2[i] = -1;
		}


		for (int i = M; i--;)
		{
			scanf("%d %d %lld", &from, &to, &dist);
			Balabong_adj[from].push_back({ from,to,dist,-1 });
			Balabong_adj[to].push_back({ to,from,dist,-1 });
			Balabong_outDegree[to]++;
			Balabong_outDegree[from]++;

		}

		int roadSize = 0;
		int next,now,store;
		long long dist;
		long long longestDist = 0;


		for (int i = 0; i < N; i++)
		{
			if (Balabong_outDegree[i] == 1)
			{
				pq.push(Balabong_adj[i][0]);
			}

			else if (Balabong_outDegree[i] == 0)
			{
				Balabong_roadValue[roadSize] = 0;
				roadSize++;
			}
		}

		while (!pq.empty())
		{
			edge = pq.top();
			pq.pop();

			if (Balabong_visit[edge.from]) continue;
			Balabong_visit[edge.from] = true;

			now = edge.from;
			next = edge.to;
			dist = edge.dist;
			
			Balabong_outDegree[next]--;


			if (Balabong_outDegree[next] == 0)
			{
				Balabong_visit[next] = true;
				longestDist = Balabong_MakeMaxDistance(roadSize, next, now, dist);
				roadSize++;
				continue;
			}

			Balabong_roadMax[next] = dist;
			Balabong_prev[next] = now;

			if (Balabong_outDegree[next] == 1)
			{
				for (int i = 0; i < Balabong_adj[next].size(); i++)
				{
					if (Balabong_visit[Balabong_adj[next][i].to]) continue;
					edge.from = next;
					edge.to = Balabong_adj[next][i].to;
					edge.dist = dist + Balabong_adj[next][i].dist;
					pq.push(edge);
					break;
				}
			}

		}

		long long res = 0;

		sort(Balabong_roadValue, Balabong_roadValue + roadSize);

		if (roadSize == 1)
		{
		}
		else if (roadSize == 2)
		{
			if (N == 2)
			{
				res = L;
			}
			else if (N == 4)
			{
				res = Balabong_roadValue[0] + Balabong_roadValue[1] + L;
			}
			else
			{
				res = Balabong_max(Balabong_roadValue[0] + Balabong_roadValue[1] + L, (L << 1) + Balabong_roadValue[0]);
			}
		}
		else
		{
			res = Balabong_max((L << 1) + Balabong_roadValue[roadSize - 2] +  Balabong_roadValue[roadSize - 3], L + Balabong_roadValue[roadSize - 1] + Balabong_roadValue[roadSize - 2]);
		}
		res = Balabong_max(res, longestDist);
		printf("#%d %lld\n", tc, res);
	}
	return 0;
}