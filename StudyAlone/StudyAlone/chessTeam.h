#pragma once
#include<iostream>
#include<vector>
#include<queue>
#include<set>
#include<functional>
#include<cstring>
using namespace std;

int max(int x1, int x2)
{
	return x1 > x2 ? x1 : x2;
}
void chessTeam()
{
	vector<pair<int, int> > player;
	int DP[1001][16][16], w, b;
	memset(DP, 0, sizeof(DP));
	int temp1, temp2;

	player.clear();
	while (
		cin >> temp1 >> temp2)
	{
		player.push_back(make_pair(temp1, temp2));
	}

	for (auto it : player)
	{
		cout << it.first << " " << it.second << endl;
	}


	int vecSize = player.size();
	
	for (int i = 1; i <= vecSize; i++)
	{
		for ( w = 0; w <= 15; w++)
		{
			for ( b = 0; b <= 15; b++)
			{
				pair<int, int> stat = player[i - 1];
				if (b > 0)
				{
					DP[i][w][b] = max(DP[i - 1][w][b], DP[i][w][b]);
					DP[i][w][b] = max(DP[i][w][b], DP[i-1][w][b-1] + stat.second);
				}

				if (w > 0)
				{
					DP[i][w][b] = max(DP[i - 1][w][b], DP[i][w][b]);
					DP[i][w][b] = max(DP[i-1][w - 1][b] + stat.first, DP[i][w][b]);
				}
			}
		}
	}
	cout << DP[vecSize][15][15] << endl;
	cin.clear();
}