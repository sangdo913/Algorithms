//파이의 합
#pragma once
#include<iostream>
#include<vector>

using namespace std;
long long pi[1000001];
int prime[1000001];

int SWEA3954() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);

	int t;

	cin >> t;

	for (int i = 2; i <= 1000000; i++) {
		if (prime[i]) continue;

		for (int j = i; j <= 1000000; j += i) {
			prime[j] = i;
		}
	}

	for (int i = 1; i <= 1000000; i++) {
		pi[i] = i;

		int num = i;
		int p = prime[num];

		while (prime[num]) {
			pi[i] = pi[i] / prime[num] * (prime[num]-1);

			p = prime[num];

			while (prime[num] == p) {
				num /= prime[num];
			}
		}

		pi[i] += pi[i - 1];
	}


	for (int tc = 1; tc <= t; tc++) {
		int a, b;
		cin >> a >> b;
		
		cout << '#' << tc << ' ' << pi[b] - pi[a - 1] << '\n';
	}
	return 0;
}
