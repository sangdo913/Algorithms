#pragma once
#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

void JangHoon()
{
	int K, N;
	cin >> K;

	for (int t = 1; t <= K; t++)
	{
		vector<int> people;
		int num, height;
		int result = INT32_MAX;
		cin >> num>> height;
		people.resize(num);

		//init
		for (int i = 0; i < num; i++)
		{
			cin >> people[i];
		}

		for (int i = 1; i < (1 << num); i++)
		{
			int temp = 0;
			for (int j = 0; j < num; j++)
			{
				if (i & (1 << j)) temp += people[j];
			}
			result = (temp >= height) && (temp < result) ? temp : result;
		}
		cout << "#" << t << " " << result-height << endl;
	}
}