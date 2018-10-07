//https://www.acmicpc.net/problem/12001
//BOJ12001 ¼Ò¹®Á¦
#pragma once
#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

vector<int> X;
vector<int> Y;
struct COD {
	int x, y;
};
vector<COD> cows;

int nums[4];

int MIN(int i1, int i2) { return i1 < i2 ? i1 : i2; }
int MAX(int i1, int i2) { return i1 < i2 ? i2 : i1; }

int getM(int a, int b) {
	nums[0] = nums[1] = nums[2] = nums[3] = 0;

	for (int i = 0; i < cows.size(); i++) {
		if (cows[i].x < a && cows[i].y < b) {
			nums[0]++;
		}
		else if (cows[i].x < a && cows[i].y > b) {
			nums[1]++;
		}
		else if (cows[i].x > a && cows[i].y < b) {
			nums[2]++;
		}
		else nums[3]++;
	}

	int res = nums[0];

	for (int i = 1; i < 4; i++) {
		res = MAX(res, nums[i]);
	}
	return res;
}

int BOJ12001() {
	int n, b;
	cin >> n >> b;

	for (int i = 0; i < n; i++) {
		int x, y;
		cin >> x >> y;

		cows.push_back({ x,y });

		X.push_back(x+1);
		X.push_back(x - 1);
		Y.push_back(y-1);
		Y.push_back(y + 1);
	}

	sort(X.begin(), X.end());
	sort(Y.begin(), Y.end());
	
	X.resize(unique(X.begin(), X.end()) - X.begin());
	Y.resize(unique(Y.begin(), Y.end()) - Y.begin());

	int res = 0x3f3f3f3f;

	for (int i = 0; i < X.size(); i++) {
		for (int j = 0; j < Y.size(); j++) {
			res = MIN(res, getM(X[i],Y[j]));
		}
	}
	cout << res;

	return 0;
}
