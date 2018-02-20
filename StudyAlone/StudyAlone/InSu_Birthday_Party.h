#pragma once
#include<iostream>
using namespace std;

int dis[1001][1001];

void init(int &M, int &N, int &x, int &y, int &c, int &X)
{
	cin >> N >> M >>X;
	for (int i = 1; i <= N; i++)
		for (int j = 1; j <= N; j++)
			dis[i][j] = 50000;

	for (int i = 0; i < M; i++)
	{
		cin >> x >> y >> c;
		dis[x][y] = c;
	}
	for (int i = 1; i <= N; i++) dis[i][i] = 0;

}

void Floyd(int N)
{
	for (int via = 1; via <= N; via++)
	{
		for (int st = 1; st <= N; st++)
			for (int dt = 1; dt <= N; dt++)
			{
					if(dis[st][dt] > dis[st][via] + dis[via][dt])
					{
						dis[st][dt] = dis[st][via] + dis[via][dt];
					}
			}
	}
}
inline int InSu_GetMax(int x1, int x2)
{
	return x1 > x2 ? x1 : x2;
}
int InSu_BIrthday_Party()
{
	int max, T, M, N, x, y, c, X;
	cin >> T;
	for (int tc = 1; tc <= T; tc++)
	{
		init(M,N,x,y,c,X);
		max = -1;
		Floyd(N);
		for (int i = 1; i <= N; i++)
		{
			max = InSu_GetMax(max, dis[i][X] + dis[X][i]);
		}
		cout << '#' << tc << ' ' << max << endl;
	}
	return 0;
}