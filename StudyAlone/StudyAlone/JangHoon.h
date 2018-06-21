#pragma once
#include<iostream>
#include<vector>
//#include<algorithm>
//using namespace std;
//
//void JangHoon()
//{
//	int K, N;
//	cin >> K;
//
//	for (int t = 1; t <= K; t++)
//	{
//		vector<int> people;
//		int num, height;
//		int result = INT32_MAX;
//		cin >> num>> height;
//		people.resize(num);
//
//		//init
//		for (int i = 0; i < num; i++)
//		{
//			cin >> people[i];
//		}
//
//		for (int i = 1; i < (1 << num); i++)
//		{
//			int temp = 0;
//			for (int j = 0; j < num; j++)
//			{
//				if (i & (1 << j)) temp += people[j];
//			}
//			result = (temp >= height) && (temp < result) ? temp : result;
//		}
//		cout << "#" << t << " " << result-height << endl;
//	}
//}

#include<cstdio>
#include<cstring>

int people[20], n, B;
int max;
bool check[200001];

int JangHoon()
{
	int t;
	scanf("%d\n", &t);

	for (int tc = 1; tc <= t; tc++)
	{
		memset(check, 0, sizeof(check));
		scanf("%d %d\n", &n, &B);
		int max = 0;

		for (int i = 0; i < n; i++)
		{
			scanf("%d \n", &people[i]);

			for (int j = max; j >= 0; j--)
			{
				if (check[j])
				{
					check[j + people[i]] = true;
				}
			}

			max += people[i];
			check[people[i]] = true;
		}

		int i;
		for (i = B; i <= max; i++)
		{
			if (check[i]) break;
		}

		printf("#%d %d\n", tc, i - B);
	}
	return 0;
}