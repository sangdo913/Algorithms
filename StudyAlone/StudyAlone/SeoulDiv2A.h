#pragma once
#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

vector<long long> vec;
int Seoul2A() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);

	int n, k;
	cin >> n >> k;
	
	for(int i = 0; i < n; i++){
		int in;
		cin >> in;
		vec.push_back(in);
	}
	sort(vec.begin(), vec.end());

	long long res = 0;
	int num = 0;
	for (int i = 1; i <= n; i++) {
		res += num * vec[i - 1];
		num++;
		num = num > k ? k : num;
	}
	
	cout << res << '\n';
	return 0;
}