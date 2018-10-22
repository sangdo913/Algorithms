#pragma once
#include<iostream>
#include<cstring>

using namespace std;

struct TOP {
	int topni;
	bool getUP() {
		return topni & 1;
	}
	bool getRIGHT() {
		return topni & (1 << 2);
	}
	bool getLEFT() {
		return topni & (1 << 6);
	}

	void rotate(int dir) {
		if (dir == 1) {
			bool temp = topni & 0b10000000;
			topni <<= 1;
			topni |= temp;
			topni &= 0xff;
		}
		else if(dir == -1){
			bool temp = topni & 1;
			topni >>= 1;
			topni |= (temp << 7);
		}
	}
	void set(int v) {
		for (int i = 0; i < 8; i++) {
			topni <<= 1;
			topni += v % 10;
			v /= 10;
		}
	}
}tops[5];

int flag[5];

int BOJ14891() {
	for (int i = 1; i <= 4; i++) {
		int n;
		cin >> n;
		tops[i].set(n);
	}

	int m;
	cin >> m;
	while (m--) {
		memset(flag, 0, sizeof(flag));

		int n, r;
		cin >> n >> r;
		flag[n] = r;

		for (int i = n-1; i >= 1; i--) {
			if (tops[i + 1].getLEFT() ^ tops[i].getRIGHT()) { flag[i] = -flag[i + 1]; }
			else break;
		}

		for (int i = n + 1; i <= 4; i++) {
			if (tops[i - 1].getRIGHT() ^ tops[i].getLEFT()) flag[i] = -flag[i - 1];
			else break;
		}
		for (int i = 1; i <= 4; i++) {
			tops[i].rotate(flag[i]);
		}
	}

	int res = 0;
	for (int i = 1; i <= 4; i++) {
		res += (tops[i].getUP() << (i-1));
	}
	cout << res;

	return 0;
}
