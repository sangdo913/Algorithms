//https://www.acmicpc.net/problem/15662
//BOJ 15662 Åé´Ï¹ÙÄû(2)
#pragma once
#include<iostream>
#include<cstring>

typedef enum { TOP = 1, RIGHT = 1 << 2, DOWN = 1 << 4, LEFT = 1 << 6 };
using namespace std;

struct topni {
	int nums;
	bool get(int flag) {
		return bool(nums & flag);
	}

	topni(int n) {
		nums = 0;
		for (int i = 0; i < 8; i++) {
			nums <<= 1;
			nums += n % 10;
			n /= 10;
		}
	}
	topni() : nums(0) {}
	
	void turn(int flag) {
		if (flag == 1) {
			int temp = bool(nums & (1<<7));
			nums <<= 1;
			nums |= (temp);
			nums &= 0b11111111;
		}
		else if(flag == -1){
			int temp = bool(nums & 1) <<7;
			nums >>= 1;
			nums |= temp;
		}
	}
};

int t, k;
int isturn[1001];
topni tops[1001];

int BOJ15662() {
	cin >> t;
	for (int i = 1; i <= t; i++) {
		int num;
		cin >> num;
		tops[i] = topni(num);
	}

	cin >> k;

	while (k--) {
		int tn;
		memset(isturn, false, sizeof(isturn));
		cin >> tn;
		cin >> isturn[tn];

		int idx = tn;
		int left = idx - 1;

		while (left) {
			if (tops[left].get(RIGHT) ^ tops[idx].get(LEFT)) {
				isturn[left] = -isturn[idx];
				idx = left;
				left = idx - 1;
			}
			else break;
		}

		idx = tn;
		int right = idx + 1;

		while (right <= t) {
			if (tops[right].get(LEFT) ^ tops[idx].get(RIGHT)) {
				isturn[right] = -isturn[idx];
				idx = right;
				right = idx + 1;
			}
			else break;
		}

		for (int i = 1; i <= t; i++) {
			tops[i].turn(isturn[i]);
		}
	}
	int res = 0;

	for (int i = 1; i <= t; i++) {
		res += tops[i].get(TOP);
	}

	cout << res;
	return 0;
}
