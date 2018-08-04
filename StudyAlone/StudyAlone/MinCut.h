#pragma once
#include<iostream>
#include<cstring>
#include<queue>
#include<vector>
#include<map>
using namespace std;
static char _map[100][100];
static const int UP = 0;
static const int DOWN = 1;
static const int LEFT = 2;
static const int RIGHT = 3;
struct Position
{
	int x;
	int y;
};

bool Validind(int x,int y, int M, int N)
{
	return !(x < 0 || x >= M || y < 0 || y>=N);
}
int MinCut_Min(int x, int y)
{
	return x < y ?  x : y;
}

void MinCut()
{
	map<pair<int, int> ,int> f;
	map<pair<int, int>,int>  c;
	vector<int> adj[20000];
	int N, M, max_flow = 0;
	char input;
	cin >> N >> M;

	if (N == 1 && M == 1)
	{
		cout << -1 << endl;
		return;
	}
	Position s, t;
	int dp[4] = { 0,0,-1,1 };
	int dx[4] = { 0,0,-1,1 };
	int dy[4] = { -1,1,0,0 };

	memset(_map, 0, sizeof(_map));
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < M; j++)
		{
			cin >> _map[i][j];

			switch (_map[i][j])
			{
			case 'K':
				s.x = j;
				s.y = i;
				break;
			case 'H':
				t.x = j;
				t.y = i;
				break;
			case '.':
				c[{2 * (i*M + j), 2 * (i*M + j) + 1}] = 1;
				f[{2 * (i*M + j), 2 * (i*M + j) + 1}] = 0;
				adj[2 * (i*M + j)].push_back(2 * (i*M + j)+1);
				adj[2 * (i*M + j)+1].push_back(2 * (i*M + j));
				if (Validind(j,i,M,N) && _map[i][j - 1] == '.')
				{
					c[{2 * (i*M + j - 1) + 1, 2 * (i*M + j)}] = 10;
					c[{2 * (i*M + j) + 1, 2 * (i*M + j - 1)}] = 10;

					f[{2 * (i*M + j - 1) + 1, 2 * (i*M + j)}] = 0;
					f[{2 * (i*M + j) + 1, 2 * (i*M + j - 1)}] = 0;

					adj[2 * (i*M + j - 1)+1].push_back(2 * (i*M + j));
					adj[2 * (i*M + j) + 1].push_back(2 * (i*M + j - 1));

					adj[2 * (i*M + j - 1) ].push_back(2 * (i*M + j)+1);
					adj[2 * (i*M + j) ].push_back(2 * (i*M + j - 1)+1);
				}
				if (Validind(j,i,M,N) && _map[i-1][j] == '.')
				{
					c[{2 * (i*M + j - M) + 1, 2 * (i*M + j)}] = 10;
					c[{2 * (i*M + j) + 1, 2 * (i*M + j - M)}] = 10;

					f[{2 * (i*M + j - M) + 1, 2 * (i*M + j)}] = 0;
					f[{2 * (i*M + j) + 1, 2 * (i*M + j - M)}] = 0;

					adj[2 * (i*M + j - M) + 1].push_back(2 * (i*M + j) );
					adj[2 * (i*M + j) + 1].push_back(2 * (i*M + j - M) );

					adj[2 * (i*M + j - M) ].push_back(2 * (i*M + j)+1);
					adj[2 * (i*M + j) ].push_back(2 * (i*M + j - M)+1);
				}
				break;
			default:
				c[{2 * (i*M + j), 2 * (i*M + j) + 1}] = 0;
				break;
			}
		}
	}

	dp[UP] = -M;
	dp[DOWN] = M;
	//S & T capacity manipulate
	for (int i = 0; i < 4; i++)
	{
		int st = s.x + s.y*M;
		int dt = st + dp[i];

		if (Validind(s.x+dx[i],s.y+dy[i],M,N)&& _map[dt/M][dt%M] !='#')
		{
			c[{st * 2 + 1, dt * 2}] = 10;
			f[{st * 2 + 1, dt * 2}] = 0;
			adj[st * 2 + 1].push_back(dt * 2);
		}

		dt = t.x + t.y*M;
		st = dt + dp[i];
		if (Validind(t.x+dx[i],t.y+dy[i], M,N) && _map[st / M][st%M] != '#')
		{
			c[{st * 2 + 1, dt * 2}] = 10;
			f[{st * 2 + 1, dt * 2}] = 0;
			adj[st * 2 + 1].push_back(dt * 2);
		}
	}

	bool check[20000];
	int prev[20000];
	int start = 2*(s.x + s.y*M) + 1;
	int end = 2*(t.x + t.y*M);
	//find network Flow
	while (true)
	{
		memset(check, false, sizeof(check));
		memset(prev, -1, sizeof(prev));
		queue<int> nodes;
		nodes.push(start);
		check[start] = true;
		bool isEnd = false;
		//find destination

		//cout << "start\n";
		while (!nodes.empty() && !isEnd)
		{
			int now =  nodes.front();
			//cout << now/2 << endl;
			nodes.pop();
			check[now] = false;
			int next;
			for (int i = 0; i < adj[now].size(); i++)
			{
				next = adj[now][i];
				if (check[next]) continue;
				if (prev[next] != -1) continue;
				if (c[{now, next}] - f[{now, next}] <= 0) continue;
				if (next == end)
				{
					prev[next] = now;
					isEnd = true;
					break;
				}
				else
				{
					prev[next] = now;
					check[next] = true;
					nodes.push(next);
				}
			}
		}

		//there is no other way to go T
		if (prev[end] == -1)
		{
			break;
		}

		//check Min length
		int minLength = c[{prev[end], end}] - f[{prev[end], end}];
		for (int now = prev[end]; now != start; now = prev[now])
		{
			minLength = MinCut_Min(minLength, c[{prev[now], now}] - f[{prev[now], now}]);
		}

		//sum every edge by minLength
		for (int now = end; now != start; now = prev[now])
		{
		//	cout << prev[now]/2 << " ";
			f[{prev[now], now}] += minLength;
			f[{now, prev[now]}] -= minLength;
		}

	//	cout << endl;

		max_flow += minLength;
	}

	max_flow = (max_flow > 5) ? -1 : max_flow;
	cout << max_flow << endl;
}
