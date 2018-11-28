//codeforces 481 F
//Mentors

#pragma once
#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

vector<int> pa[200001];
vector<int> r;
vector<int> nums;
int check[200001];
int res[200001];
int n, k;

struct cmp {
	bool operator()(int i1, int i2) {
		return r[i1] < r[i2];
	}
};

int F481() {
	cin >> n >> k;

	for (int i = 0; i < n; i++) {
		nums.push_back(i + 1);
	}

	r.push_back(0);

	for (int i = 0; i < n; i++) {
		int num = 0;
		cin >> num;
		r.push_back(num);
	}

	for (int i = 0; i < k; i++) {
		int f, t;
		cin >> f >> t;

		pa[t].push_back(f);
		pa[f].push_back(t);
	}

	sort(nums.begin(), nums.end(), cmp());

	int e = 0;
	for (int i = 0; i < n; i++) {
		int now = nums[i], cnt = 0;
		if (r[now] > r[nums[e]]) e = i;
		for (int ii = 0; ii < pa[now].size(); ii++) cnt += check[pa[now][ii]]&& r[now] != r[pa[now][ii]];
		res[now] = e - cnt;
		check[now] = true;
	}

	for (int i = 1; i <= n; i++) cout << res[i] << ' ';
	cout << endl;
	return 0;
}
