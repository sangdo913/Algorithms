#pragma once
#include<iostream>
#include<vector>

using namespace std;

vector<int> primes;
bool nprime[1000];
int nums[1000];

int C381() {
	primes.push_back(2);
	for (int i = 3; i <= 999; i += 2) {
		if (!nprime[i]) primes.push_back(i);
		for (int j = 3*i; j <= 999; j += 2*i) {
			nprime[j] = true;
		}
	}
	for (int i = 0; i < primes.size(); i++) {
		for (int j = i ; j < primes.size(); j++) {
			for (int k = j ; k < primes.size(); k++) {
				int num = primes[i] + primes[j] + primes[k];
				if (num < 1000) nums[num]++;
			}
		}
	}

	int t;
	cin >> t;
	for (int tc = 1; tc <= t; tc++) {
		int n;
		cin >> n;
		int res = 0;
		cout << '#' << tc << ' ' << nums[n] << '\n';
	}
	return 0;
}