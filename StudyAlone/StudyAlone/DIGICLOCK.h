#pragma once
#include<cstdio>
#include<cstdio>
int conv[1 << 8];

void init() {
	conv[0b0110000] = 1;
	conv[0b1101101] = 2;
	conv[0b1111001] = 3;
	conv[0b1110010] = 4;
	conv[0b1011011] = 5;
	conv[0b1011111] = 6;
	conv[0b0110001] = 7;
	conv[0b1111111] = 8;
	conv[0b1111011] = 9;
	conv[0b0111111] = 0;
}

int digit[4][7];

int convert() {
	int res = 0;
	for (int i = 0; i < 4; i++) {
		res *= 10;
		int idx = 0;
		for (int j = 0; j < 7; j++) {
			idx <<= 1;
			idx += digit[i][j];
		}
		int num = conv[idx];
		if (num == 10) return 50000;
		res += conv[idx];
	}

	return (res / 100 > 23) || (res % 100 > 59) ? 50000 : res;
}

int min(int i1, int i2) {
	return i1 > i2 ? i2 : i1;
}

int turnOff(int depth) {
	if (depth == 0) {
		return convert();
	}

	int ret = convert();
	
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 7; j++) {
			if (digit[i][j]) {
				digit[i][j] = 0;
				ret = min(ret, turnOff(depth - 1));
				digit[i][j] = 1;
			}
			else {
				digit[i][j] = 1;
				ret = min(ret, turnOff(depth - 1));
				digit[i][j] = 0;
			}
		}
	}
	return ret;
}

int DIGICLOCK() {
	int t;
	scanf("%d\n", &t);
	for (int i = 0; i < 1 << 8; i++) {
		conv[i] = 10;
	}

	init();

	for (int tc = 1; tc <= t; tc++) {
		for (int i = 0; i < 4; i++) {
			for (int j = 6; j >= 0; j--) {
				scanf("%d \n", &digit[i][j]);
			}
		}

		int ret = turnOff(2);
		printf("#%d %d %d\n", tc, ret / 100, ret % 100);
	}
	return 0;
}