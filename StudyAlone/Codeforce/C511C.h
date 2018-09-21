#pragma once
#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

int nums[15000001];
int nprime[15000001];

int pr[10000000];
int pcnt = 0;

int gcd(int a, int b) {
	if (a < b) {
		int temp = a;
		a = b;
		b = temp;
	}

	int r;
	while (b) {
		r = a % b;
		a = b;
		b = r;
	}
	return a;
}

int arr[400000];

int MAX(int i1, int i2) { return i1 < i2 ? i2 : i1; }

int C511C() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);

	int n;
	pr[pcnt++] = 2;
	for (int i = 3; i <= 15000001; i+=2) {
		if (nprime[i]) continue;
		pr[pcnt++] = i;
		//primes.push_back(i);

		for (int j = i; j <= 15000001; j += 2*i) {
			nprime[i] = true;
		}
	}

	cin >> n;
	for (int i = 0; i < n; i++) {
		cin >> arr[i];
	}

	int g = arr[0];
	for (int i = 1; i < n ; i++) {
		g = gcd(g, arr[i]);
	}

	for (int i = 0; i < n; i++) {
		arr[i] /= g;
	}

	int max = 1;

	bool isone = true;
	for (int i = 0; i < n; i++) {
		if (arr[i] != 1) {
			isone = false;
			break;
		}
	}

	if (isone) {
		cout << -1; return 0 ;
	}

	for (int i = 0; i < n; i++) {
		int j;
		for ( j = 0; j < pcnt-1 && pr[j]*pr[j] < arr[i]; j++) {
			if (arr[i] % pr[j] == 0) {
				nums[pr[j]]++;
				nums[arr[i] / pr[j]]++;
				max = MAX(max, nums[pr[j]]);
				max = MAX(max, nums[arr[i] / pr[j]]);
			}
		}
		if (pr[j] * pr[j] == arr[i]) {
			nums[pr[j]]++;
			max = MAX(nums[pr[j]], max);
		}

		if (arr[i] != 1 && find(pr, pr + pcnt, arr[i]) != pr+pcnt) {
			nums[arr[i]]++;
			max = MAX(nums[arr[i]], max);
		}
	}
/*
	for (int i = 0; i < primes.size(); i++) {
		int cnt = 0;
		for (int j = 0; j < n; j++) {
			if (arr[j] % primes[i] == 0) {
				cnt++;
			}
		}
		max = MAX(max, cnt);
	}*/
	cout << n - max;
	return 0;
}
