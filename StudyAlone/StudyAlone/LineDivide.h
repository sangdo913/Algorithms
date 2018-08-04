#pragma once
#include<iostream>
#include<cstdio>
using namespace std;

int contries[10001];
void LineDivide()
{
	int T, N, M;
	int min_value, sum,value,ind;
	std::ios::sync_with_stdio(false);
	cin >> T;
	for (int tc = 1; tc <= T; tc++)
	{
		cin >> N >> M;
		char where;
		ind = value = min_value = 0;
		for (int i = 0; i <= N; i++) contries[i] = 0;

		for (int cnt = 0; cnt < M; cnt++)
		{
			for (int i = 0; i < N; i++)
			{
				cin >> where;
				sum = where == 'E' ? 1 : -1;
				contries[i + 1] += sum;
			}
		}
		
		for (int i = 1; i <=N; i++)
		{
			value += contries[i];
			if (min_value > value)
			{
				ind = i;
				min_value = value;
			}
		}

		cout << '#' << tc << ' ' << ind << ' ' << ind + 1 << endl;
	}
}