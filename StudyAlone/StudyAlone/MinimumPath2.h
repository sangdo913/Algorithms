#pragma once
#include<iostream>
#include<vector>
#include<cmath>
#include<queue>
#include<stack>

using namespace std;

struct Client
{
	int x;
	int y;
};

int CalDistance(Client c1, Client c2)
{
	return abs(c1.x - c2.x) + abs(c1.y - c2.y);
}
int getBitNum(int x)
{
	int cnt = 0;
	while (x > 0)
	{
		if (x & 1) cnt++;
		x = x >> 1;
	}

	return cnt;
}

int Min(int x, int  y)
{
	return x > y ? y : x;
}

int TPS(const vector<Client> &info, vector<vector<int> > & dp, int visit,int st)
{
	int num_of_client = info.size();
	if (visit == (1 << (num_of_client-2)) - 1)
		return CalDistance(info[0],info[st]);
	if (getBitNum(visit) > 1 && dp[st][visit] != 0) return dp[st][visit];

	int &result = dp[st][visit];
	result = INT32_MAX;

	for (int i = 2; i < num_of_client; i++)
	{
		if(!(visit & 1<<(i-2)))
			result = Min(dp[st][visit], TPS(info, dp, visit | 1<<(i-2), i)+CalDistance(info[st],info[i]));
	}
	return result;
}

void InitClient(const vector<Client> &info,vector<vector<int> > &dp)
{
	int size = dp.size();
	for (int i = 2; i < size; i++)
	{
		dp[i][1 << (i-2)] = CalDistance(info[0], info[i]);
	}
}

void GetInput(vector<Client> &info)
{
	int size = info.size();

	for (int i = 0; i < size; i++)
	{
		cin >> info[i].x >> info[i].y;
	}
}
void MinimumPath2()
{
	int T;
	cin >> T;
	for (int tc = 1; tc <= T; tc++)
	{
		int num_of_client;
		cin >> num_of_client;

		vector<Client> clients;
		vector<vector<int> > dp;
		
		clients.resize(num_of_client + 2);
		dp.resize(num_of_client + 2);

		GetInput(clients);

		for (int i = 0; i < num_of_client + 2; i++)
		{
			dp[i].resize(1 << num_of_client);
		}

		InitClient(clients, dp);
		int result = INT32_MAX;

		for (int i = 2; i < num_of_client + 2; i++)
			result = Min(result, TPS(clients, dp, 1 << (i - 2), i) + CalDistance(clients[i],clients[1]));
		cout << "#" << tc << " " << result << endl;
	}
}