#pragma once
#include<iostream>
#include<vector>

using namespace std;
vector<int> primes;

bool notprime[500000];

bool isprime(long long a) {
	for (int i = 0; i < primes.size() && primes[i] < a; i++) {
		if (a%primes[i] == 0) return false;
	}
	return true;
}

int LyftLevel5B() {
	long long a, b;
	int t;
	cin >> t;
	primes.push_back(2);
	for (int i = 3; i <= 500000; i+=2) {
		if (notprime[i]) continue;
			primes.push_back(i);

		for (int j = i; j <= 500000; j += 2 * i) {
			notprime[j] = true;
		}
	}
	while (t--) {

		cin  >> a >> b;
		if (a - b == 1 && isprime(a+b) ) cout << "YES\n";
		else cout << "NO\n";
	}


	return 0;
}
