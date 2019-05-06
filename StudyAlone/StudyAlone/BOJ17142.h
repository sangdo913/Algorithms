#include<iostream>
#define SIZE 10000 

using namespace std;

int arr0[50][50];
int arr[50][50];

int que[SIZE];

int dr[4] = { -1,0,1,0 };
int dc[4] = { 0,1,0,-1 }, n,m,re,fr;
int x[2500], y[2500];

int getcnt(int remain) {
	int ret = 0;
	if (remain == 0) return 0;

	while (re%SIZE != fr % SIZE) {
		ret++;
		int cnt = (SIZE + (re % SIZE) - (fr % SIZE)) % SIZE;
		while (cnt--) {
			int now = que[fr++%SIZE];

			for (int d = 0; d < 4; ++d) {
				int nr = now / n + dr[d];
				int nc = now % n + dc[d];
				if (nr < 0 || nc < 0 || nr ==n || nc == n || arr[nr][nc] <= ret) {
					continue;
				}
				arr[nr][nc] = ret;
				que[re++%SIZE] = nr * n + nc;
				if ((remain -= arr0[nr][nc]==0) == 0) return ret;
			}
		}
	}
	return 0x3f3f3f3f;
}

int getZero(int i) {
	int ret = 0;
	while ((i & 1) == 0) ret++, i >>= 1;
	return ret;
}

bool check() {
	for (int i = 0; i < n; ++i) for (int j = 0; j < n; ++j) if (arr0[i][j] == 0 && arr[i][j] == 0x3f3f3f3f) return false;
	return true;
}

int ain() {
	cin >> n >> m;
	int bnum = 0;
	int remain = 0;
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < n; ++j) {
			cin >> arr0[i][j];
			if (arr0[i][j] == 2) {
				x[bnum] = i;
				y[bnum++] = j;
			}
			else if (arr0[i][j] == 0) ++remain;
		}
	}

	int res = 0x3f3f3f3f;
	int bit = (1 << m) - 1;
	while (bit < (1 << bnum)) {
		int temp = bit | ((bit &-bit) - 1);

		for (int i = 0; i < n; ++i) for (int j = 0; j < n; ++j) {
			if (arr0[i][j] == 1) {
				arr[i][j] = -1;
			}
			else arr[i][j] = 0x3f3f3f3f;
		}

		fr = re;

		for (int id = 0; id < bnum; ++id) {
			if (bit & (1 << id)) {
				que[re++%SIZE] = x[id] * n + y[id]; arr[x[id]][y[id]] = 0;
			}
		}

		int cnt = getcnt(remain);
		res = cnt < res ? cnt : res;

		bit = (temp + 1) | (((~temp & -~temp) - 1) >> (getZero(bit) + 1));
		
	}

	cout << (res == 0x3f3f3f3f ? -1 :res);
	return 0;
}
