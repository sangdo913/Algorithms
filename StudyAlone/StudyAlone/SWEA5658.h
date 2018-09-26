//https://www.swexpertacademy.com/main/code/problem/problemDetail.do?contestProbId=AWXRUN9KfZ8DFAUo
//SWEA 5658 보물상자 비밀번호
#pragma once
#include<iostream>
#include<set>
#include<algorithm>

using namespace std;

set<int> se;

int conv[256];
int nums[28], n;

int make() {
	int num = 0;
	for (int i = 0; i < n / 4; i++) {
		num <<= 4;
		num += nums[i];
	}

	for (int i = n / 4; i < n + n / 4; i++) {
		num -= nums[(i - n / 4)] << (4 * (n / 4 - 1));
		num <<= 4;
		num += nums[i%n];

		se.insert(-num);
	}
	return 0;
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);

	int t;

	cin >> t;

	int v = 0;
	for (int i = 0; i < 10; i++) {
		conv['0' + i] = v++;
	}

	for (int i = 'A'; i <= 'F'; i++) {
		conv[i] = v++;
	}

	for (int tc = 1; tc <= t; tc++) {
		int k;
		cin >> n >> k;

		for (int i = 0; i < n; i++) {
			char in;
			cin >> in;
			nums[i] = conv[in];
		}

		se.clear();

		make();

		int order = 1;
		int res;

		for (auto it : se) {
			if (order++ == k) {
				res = -it;
				break;
			}
		}

		cout << '#' << tc << ' ' << res << '\n';
	}
	return 0;
}
