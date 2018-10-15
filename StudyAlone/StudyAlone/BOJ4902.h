//https://www.acmicpc.net/problem/4902
//BOJ 4902 »ï°¢ÇüÀÇ °ª
#pragma once
#include<iostream>

using namespace std;

int nums[401][801];
int MAX(int i1, int i2) { return i1 < i2 ? i2 : i1; }

int BOJ4902() {

	int n;
	int t = 1;
	while (true) {
		cin >> n;
		if (n == 0) break;

		int res = -10000;
		for (int i = 1; i <= n ; i++) {
			for (int j = 1; j < i*2; j++) {
				cin >> nums[i][j];
				res = MAX(res, nums[i][j]);
				nums[i][j] += nums[i][j - 1];
			}
		}

		for (int i = 1; i <= n; i++) {
			for (int j = 1; j < 2*i; j+=2) {
				int temp = nums[i][j] - nums[i][j - 1];
					
				int l = 1;
				while (i + l <= n) {
					temp += nums[i+l][j + 2 * l] - nums[i+l][j - 1];
					res = MAX(res, temp);
					l++;
				}
			}
		}

		for (int i = n; i >= 1; i--) {
			for (int j = 2; j < i * 2; j+=2) {
				int temp = nums[i][j] - nums[i][j - 1];

				int l = 1;
				while (i - l > 0 && j - 2 * l > 0 && (i-l)*2 > j) {
					temp += nums[i - l][j] - nums[i - l][j - 2 * l - 1];
					res = MAX(res, temp);
					l++;
				}
			}
		}
		cout << t++ << ". " << res << endl;
	}
	return 0;
}