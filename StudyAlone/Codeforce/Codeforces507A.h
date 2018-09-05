#pragma once
#include<iostream>
#include<cstring>
using namespace std;

int n, a[2];
int nums[22];

int Codeforces507A() {
	cin >> n >> a[0] >> a[1];
	
	for (int i = 0; i < n; i++) {
		cin >> nums[i];
	}
	int cost = 0;

	for (int i = 0; i < (n) / 2; i++) {
		if (nums[i] != 2 && nums[n - 1 - i] != 2 && nums[i] != nums[n - 1 - i]) {
			printf("-1\n"); return 0;
		}
		
		if (nums[i] != 2 && nums[n - 1 - i] != 2 && nums[i] == nums[n - 1 - i]) continue;

		if (nums[i] == 2 && nums[n - i - 1] == 2) {
			cost += a[0] < a[1] ? a[0] * 2 : a[1] * 2;
			continue;
		}
		if (nums[i] == 2) {
			cost += a[nums[n - 1 - i]];
		}
		else {
			cost += a[nums[i]];
		}
	}
	cost += n % 2 && nums[(n)/2] == 2 ? a[0] < a[1] ? a[0] : a[1] : 0;
	printf("%d\n", cost);
	return 0;
}