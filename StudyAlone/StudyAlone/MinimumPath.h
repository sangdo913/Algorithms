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

void InitVec(const vector<Client> info, vector<vector<int> > &init, queue<pair<int, long long> >&q)
{
	int size = info.size();
	Client company = info[0];
	for (int i = 2; i < size; i++)
	{
		init[i][1 << (i - 2)] = 0;//CalDistance(company, info[i]);
		q.push(make_pair(i,1 << (i - 2)));
	}
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
void MinimumPath()
{
	const int START = 1;
	const int INFO = 0;
	int T;
	const int company = 0, home = 1;
	cin >> T;
	for (int tc = 1; tc <= T; tc++)
	{
		vector<vector<int> >flag[2];

		int num_of_client;

		cin >> num_of_client;
		vector<Client> clients;
		clients.resize(num_of_client+2);

		flag[INFO].resize(num_of_client + 2);
		flag[START].resize(num_of_client + 2);

		for (int i = 0; i < num_of_client + 2; i++)
		{
			flag[INFO][i].resize((1 << num_of_client), INT32_MAX);
			flag[START][i].resize((1 << num_of_client), -1);
		}
		// input
		for (int i = 0; i < num_of_client+2; i++)
		{
			cin >> clients[i].x >> clients[i].y;
		}

		queue<pair<int, long long> > store;
		InitVec(clients, flag[INFO],store);
		
		for (int i = 2; i < num_of_client + 2; i++)
		{
			flag[START][i][1] = i;
		}

		vector<vector<bool> > check;
		check.resize(num_of_client);
		for (int i = 0; i < num_of_client; i++)
			check[i].resize((1 << num_of_client));

		while (!store.empty())
		{
			int index = store.front().second;
			int cur = store.front().first;
			store.pop();

		//	bool ch = true;
		//	for (int i = 0; i < num_of_client; i++) ch &= (check[i][index] | index >> i & 1);
/*
			if (getBitNum(index) == num_of_client || ch)
			{
				index = store.top().second;
				cur = store.top().first;
				store.pop();
				
				continue;
			}*/
			int num_of_bits;
			num_of_bits = getBitNum(index);
		//	int nextIndex = index;
			for (int i = 2; i < num_of_client + 2; i++)
			{
				if (!(index & (1 << (i - 2))))
				{
					if (flag[INFO][i][((1 << num_of_client) - 1) ^ index] == INT32_MAX)
					{
						store.push(make_pair(i, index | (1 << (i - 2))));
						flag[INFO][i][index | (1 << (i - 2))] = Min(flag[INFO][cur][index] + CalDistance(clients[i], clients[cur]), flag[INFO][i][index | (1 << (i - 2))]);

						bool big_counter = flag[INFO][cur][index] + CalDistance(clients[i], clients[cur]) > flag[INFO][i][index | (1 << (i - 2))];
						flag[START][i][index | (1 << (i - 2))] = big_counter ? flag[START][cur][index] : flag[START][i][index | (1 << (i - 2))];
						//cur = i;
						//nextIndex = index | (1 << (i - 2));
						//break;
					}
					else
					{
						flag[INFO][i][(1 << (num_of_client)) - 1] = Min(flag[INFO][i][((1 << num_of_client) - 1) ^ index] + flag[INFO][cur][index], flag[INFO][i][(1 << (num_of_client)) - 1]);
						
						bool big_counter = flag[INFO][i][((1 << num_of_client) - 1) ^ index] + flag[INFO][cur][index] > flag[INFO][i][(1 << (num_of_client)) - 1];
						flag[START][i][index | (1 << (i - 2))] = big_counter ? flag[START][cur][index] : flag[START][i][index | (1 << (i - 2))];
						
						//nextIndex = (1 << num_of_client) - 1;
					}
					/*if((index | (1 << (i-2))) < (1<< num_of_client)-1
						&& flag[i][ ((1 << num_of_client) -1)&(~index) ] == INT32_MAX)store.push(make_pair(i, index | 1<< (i - 2)));*/
				}
			}

			//index = nextIndex;
		}
		int result = INT32_MAX;
		for (int i = 2; i < num_of_client+2; i++)
		{
			result = Min(result, flag[i][INFO][(1<< num_of_client)-1] + CalDistance(clients[1], clients[i]));
		}
		cout << "#" << tc << " " << result << endl; 
	}
}