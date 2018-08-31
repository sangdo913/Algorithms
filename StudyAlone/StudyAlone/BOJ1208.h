#pragma once
#include<iostream>
#include<set>
#include<functional>
#include<map>
#include<algorithm>
#include<vector>
using namespace std;
map<int, int> mp;
int BOJ1208() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);

	set<int, greater<int>> se;
	
	vector<int> vec;
	int n, k;
	
	cin >> n >> k;

	for (int i = 0; i < n; i++) {
		int in;
		vec.push_back(in);
	}
	upper_bound(vec.begin(), vec.end(), 0);
	se.insert(n);
	mp[n]++;
	
	
}