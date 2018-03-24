#pragma once
#include<iostream>
#include<vector>
#include<string>
#include<string.h>
using namespace std;

void GNS()
{
	int K , N;
	cin >> K;
	for (int t = 1; t <= K; t++)
	{
		string result;

		cin >>result>> N;
		int store[10];
		const string conv[10] = { "ZRO","ONE", "TWO", "THR", "FOR", "FIV", "SIX", "SVN", "EGT", "NIN" };
		string in;

		memset(store, 0, sizeof(store));

		for (int i = 0; i < N; i++)
		{
			cin >> in;
			for (int i = 0; i < 10;i++)
		
				if (in == conv[i])
				{
					store[i]++;
					break;
				}
		}

		cout << result << endl;
		for (int i = 0; i < 10; i++)
		{
			for (int j = 0; j < store[i]; j++)
			{
				cout << conv[i] << " ";
			}
		}
		cout << endl;

	}
}