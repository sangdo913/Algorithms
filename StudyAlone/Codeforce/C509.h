#pragma once
#include<map>
#include<iostream>
#include<vector>
#include<queue>
#include<algorithm>
#include<list>
#include<set>
using namespace std;

map<int, int> mp;
vector<int> vec;
vector<int> res;
vector<bool> check;
vector<vector<int> > days;
int C509() {
	int n, m, d;

	ios_base::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);

	cin >> n >> m >> d;
	
	for (int i = 0; i < n; i++) {
		int n;
		cin >> n;
		vec.push_back(n);
		mp[n] = i;
	}
	sort(vec.begin(), vec.end());

	res.resize(vec.size());

	check.resize(vec.size());

	int day = 0;
	for (int i = 0; i < vec.size(); i++) {
		if (check[i]) continue;
		day++;
		auto it = vec.begin() + i;
		while (it != vec.end()) {
			while (it != vec.end() && check[it - vec.begin()])it++;
			if (it == vec.end()) break;
			check[it - vec.begin()] = true;
			res[mp[*it]] = day;
			it = upper_bound(vec.begin() + i, vec.end(), vec[it-vec.begin()] + d);
		}

	}
	cout << day << '\n';
	for (auto it : res) {
		cout << it << ' ';
	}
	cout << endl;
	return 0;
}
