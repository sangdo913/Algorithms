#pragma once
#include<cstring>
#include<map>
#include<string>
#include<cstring>
#include<iostream>
using namespace std;

int nums[30001][31];

map<string, int> mp;

int hodongFindStr() {
	int t;
	scanf("%d\n", &t);

	for (int tc = 1; tc <= t; tc++) {
		int n, m;
		scanf("%d\n", &n);
		string in;
		memset(nums, 0, sizeof(nums));
		for (int i = 1; i <= n; i++) {
			cin >> in;
			mp.insert({ in,i });

			for (int i = 1; i <= 30; i++) {

			}

		}

		printf("#%d %d\n", tc, res);
	}
	return 0;
}