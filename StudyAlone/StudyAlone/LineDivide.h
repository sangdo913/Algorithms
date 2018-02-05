#pragma once
#include<iostream>
#include<cstdio>
using namespace std;

int contries[10001];
char where[100][10000];
void LineDivide()
{
	int T, N, M;
	int min_value;
	std::ios::sync_with_stdio(false);
	cin >> T;
	for (int tc = 1; tc <= T; tc++)
	{
		cin >> N >> M;
		min_value = 0;
		int value = 0;
		for (int i = 0; i <= N; i++) contries[i] = 0;

		for (int cnt = 0; cnt < M;cnt++)
		{
			for (int i = 0; i < N; i++) cin >> where[cnt][i];
		}

		int index = 0;
		for (int i = 0; i < N; i++)
		{
			for (int j = 0; j < M; j++)
			{
				int sum = where[j][i] == 'E' ? 1 : -1;
				contries[i + 1] += sum;
				value += where[j][i] == 'W';
			}
		}
		min_value = value;
		for (int i = 1; i <=N; i++)
		{
			value += contries[i];
			if (min_value > value)
			{
				index = i;
				min_value = value;
			}
		}

		cout << '#' << tc << ' ' << index << ' ' << index + 1 << endl;
	}
}