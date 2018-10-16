//
//SWEA5948 새샘이의 7-3-5 게임
#pragma once
#include<iostream>
#include<cstring>
#include<queue>

using namespace std;

int arr[7];
bool check[701];
priority_queue<int> pq;


int getZero(int n) {
	int res = 0;
	while ((n & 1) == 0) {
		res++; 
		n >>= 1;
	}
	return res;
}

void func(int bit) {
	int sum = 0;
	int idx = 0;
	while (bit) {
		if (bit & 1) {
			sum += arr[idx];
		}
		bit >>= 1;
		idx++;
	}
	if (check[sum] == false) {
		check[sum] = true;
		pq.push(sum);
	}
}

int SWEA5948() {
	ios_base::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);
	int t;
	cin >> t;

	for (int tc = 1; tc <= t; tc++) {
		memset(check, false, sizeof(check));
		for (int i = 0; i < 7; i++) cin >> arr[i];

		int bit = 0b111;
		while (bit < 1 << 7) {
			int temp = bit | ((bit&-bit) - 1);

			func(bit);

			int nb = temp + 1;
			nb |= ((~temp & -~temp) -1) >> (getZero(bit) + 1);
			bit = nb;
		}

		for (int i = 0; i < 4; i++) pq.pop();
		cout << '#' << tc << ' ' << pq.top() << '\n';
		
		while (pq.size()) pq.pop();
	}
	return 0;
}
