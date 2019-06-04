#include<iostream>

using namespace std;
bool arr[10][10];
int remain[6];

bool check() {
	for (int i = 0; i < 10; ++i) for (int j = 0; j < 10; ++j) {
		if (arr[i][j]) return false;
	}
	return true;
}
int res = 0x3f3f3f3f;
#define MIN(x,y) ((x)> (y) ? (y) : (x))

void dfs(int r, int c, int num) {
	 if (r == 10) {
		if (check()) { res = MIN(res, num); }
		return;
	}

	int nr, nc;
	nr = r, nc = c + 1;
	if (nc == 10) { nc = 0, nr++; }

	if (arr[r][c]) {
		for (int i = 1; i <= 5; ++i) {
			if (!remain[i]) {
				continue;
			}
			for (int ii = 0; ii < i; ++ii) {
				for (int jj = 0; jj < i; ++jj) {
					if (r+ii >= 10 || c + jj >= 10 ||!arr[r + ii][c + jj]) goto LOOPEND;
				}
			}
			for (int ii = 0; ii < i; ++ii) {
				for (int jj = 0; jj < i; ++jj) arr[r + ii][c + jj] = 0;
			}
			remain[i]--;
			dfs(nr, nc, num + 1);
			remain[i]++;
			for (int ii = 0; ii < i; ++ii) {
				for (int jj = 0; jj < i; ++jj) arr[r + ii][c + jj] = 1;
			}
		LOOPEND:
			continue;
		}
	}
	else {
		dfs(nr, nc, num);
	}
}

int main() {
	for (int i = 0; i < 10; ++i) for (int j = 0; j < 10; ++j) cin >> arr[i][j];
	remain[1] = remain[2] = remain[3] = remain[4] = remain[5] = 5;
	dfs(0, 0,  0);
	cout << (res == 0x3f3f3f3f ? -1 : res);

	return 0;
}
