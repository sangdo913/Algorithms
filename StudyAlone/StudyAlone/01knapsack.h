#pragma once
#include<iostream>
#include<cmath>
#include<cstring>

// 0/1knpasack https://www.swexpertacademy.com/main/code/problem/problemDetail.do?contestProbId=AWBJAVpqrzQDFAWr&categoryId=AWBJAVpqrzQDFAWr&categoryType=CODE
using namespace std;
int KNAP_INFO[2][101];
const int KANP_V = 0;
const int KANP_C = 1;
int KNAP_MAX(int x, int y)
{
	return x > y ? x : y;
}

bool KNAP_ISOUT(int x, int y, int size,int weight)
{
	return x < 0 || x >= size || y < 0 || y > weight;
}

void kanpsack() {
	int T,N, K;
	int knap_dp[101][1001];
	cin >> T;
	for (int tc = 1; tc <= T; tc++)
	{
		cin >> N >> K;
		for (int i = 1; i <= N; i++)
		{
			cin >> KNAP_INFO[KANP_V][i];
			cin >> KNAP_INFO[KANP_C][i];
		}
		memset(knap_dp, 0, sizeof(knap_dp));
		int result = 0;
		// i : the ind of things, j : Weight
		for (int i = 1; i <= N; i++)
		{
			for (int w = 0; w <= K; w++)
			{
				if (!KNAP_ISOUT(i-1, w, N,w))
				{
					knap_dp[i][w] = KNAP_MAX(knap_dp[i-1][w], knap_dp[i - 1][w]);
				}

				if (!KNAP_ISOUT(i, w - 1, N,w))
				{
					knap_dp[i][w] = KNAP_MAX(knap_dp[i-1][w], knap_dp[i-1][w-1]);
				}

				if (w - KNAP_INFO[KANP_V][i] < 0) continue;
				int selected = w - KNAP_INFO[KANP_V][i];
				knap_dp[i][w] = KNAP_MAX(knap_dp[i-1][w], knap_dp[i-1][selected] + KNAP_INFO[KANP_C][i]);
			}
		}
		result = knap_dp[N][K];
		cout << '#' << tc<<' '<< result << endl;
	}
}
