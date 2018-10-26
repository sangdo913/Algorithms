#include <iostream>
using namespace std;

struct COD {
	int r, c;
};

COD house[100];
COD wifi[13];
int hlen, wlen;

int info[100][13];
int arr[50][50];
int ABS(int i) { return i > 0 ? i : -i; }
int dist(COD c1, COD c2) {
	return ABS(c1.r - c2.r) + ABS(c1.c - c2.c);
}

int getZero(int i) {
	int res = 0;
	while ((i & 1) == 0) res++, i >>= 1;
	return res;
}

int MIN(int i1, int i2) { return i1 < i2 ? i1 : i2; }

int func(int bit) {
	int ret = 0;
	for (int i = 0; i < hlen; i++) {
		int res = 0x3f3f3f3f;
		int b = bit;
		int idx = 0;
		while (b) {
			if (b & 1) {
				res = MIN(res, info[i][idx]);
			}
			idx++, b >>= 1;
		}
		ret += res;
	}
	return ret;
}
int main()
{
	int n, m;
	cin >> n >> m;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cin >> arr[i][j];
			if (arr[i][j] == 1) {
				house[hlen].r = i;
				house[hlen].c = j;
				hlen++;
			}
			else if (arr[i][j] == 2) {
				wifi[wlen].r = i;
				wifi[wlen].c = j;
				wlen++;
			}
		}
	}

	for (int i = 0; i < hlen; i++) {
		for (int j = 0; j < wlen; j++) {
			info[i][j] = dist(house[i], wifi[j]);
		}
	}

	int bit = (1 << m) - 1;
	int res = 0x3f3f3f3f;
	while (bit < (1 << wlen)) {
		int temp = bit | ((bit & -bit) - 1);
		res = MIN(res, func(bit));

		bit = (temp + 1) | (((~temp & -~temp)-1) >> (getZero(bit)+1));
	}
	cout << res;
	return 0;
}