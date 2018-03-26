#pragma once
#include<iostream>
#include<vector>
#include<algorithm>
#include<functional>

using namespace std;

const int CONTRY_INFO = 0;
const int CONTRY_TIME = 1;

void ContryTest()
{
	int T, N, M;
	cin >> T;

	for (int t = 1; t <= T; t++)
	{
		vector<long long> info;
		long long start = 0; 
		long long end, mid;
		long long sum = 0;
		long long res = 0;
		cin >> N >> M;
		info.resize(N);
		for (int i = 0; i < N; i++)
		{
			cin >> info[i];
		}

		end = info[0] * M;
		res = end;
		while (start <= end)
		{
			mid = (start + end) / 2;
			sum = 0;
			for (int i = 0; i < N; i++)
				sum += mid / info[i];
			if (sum < M)
			{
				start = mid + 1;
			}
			else
			{
				res = mid < res? mid: res;
				end = mid - 1;
			}
			
		}

		cout << "#" << t << " " << res << endl;
	}
}