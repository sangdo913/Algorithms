#include<iostream>
#include<map>

using namespace std;

typedef unsigned long long ull;
int idx[10][10];
int ilen;

char arr[10][11];
char block[4][10][11];

map<ull, int> mp[10][10];
int best = 0;
int h, w, r, c;
int len;
void rotate() {
	for (int d = 1; d < 4; ++d) {
		for (int i = 0; i < len; ++i) {
			for (int j = 0; j < len; ++j) {
				block[d][j][len - i - 1] = block[d-1][i][j];
			}
		}
	}
	for (int d = 0; d < 4; ++d) {
		int si = 0, sj =0;
		for (; si < len; si++) {
			for (int j = 0; j < len; ++j) {
				if (block[d][si][j] == '#') goto ENDLOOP1;
			}
		}
		ENDLOOP1:
		for (int i = 0; i + si < len; ++i) {
			for (int j = 0; j < len; ++j) {
				block[d][i][j] = block[d][i + si][j];
			}
		}
		for (int i = len - si; i < len; ++i) {
			for (int j = 0; j < len; ++j) block[d][i][j] = '.';
		}

		si = 0;
		for (; si < len; si++) {
			for (int j = 0; j < len; ++j) {
				if (block[d][j][si] == '#') goto ENDLOOP2;
			}
		}
		ENDLOOP2:
		for (int j = 0; j + si < len; ++j) {
			for (int i = 0; i < len; ++i) {
				block[d][i][j] = block[d][i][j+si];
			}
		}
		for (int i = len - si; i < len; ++i) {
			for (int j = 0; j < len; ++j) block[d][j][i] = '.';
		}
	}
}

bool check(int r1, int c1, int b) {
	for (int i = 0; i < len; ++i) {
		for (int j = 0; j < len; ++j) {
			if (block[b][i][j] == '.') continue;
			if ((r1 + i >= h || c1 + j >= w)|| arr[r1+i][c1+j] == '#') return false;
		}
	}
	return true;
}

void paint(int nr, int nc, int b, char c) {
	for (int i = 0; i < len; ++i) {
		for (int j = 0; j < len; ++j) {
			if (block[b][i][j] == '#') {
				arr[i + nr][j + nc] = c;
			}
		}
	}
}
void getRes(int nr, int nc, int cnt) {
	if (nr == h) {
		best = best > cnt ? best : cnt;
		return;
	}

	ull visit = 0;
	for (int i = 0; i < len; ++i) {
		if (i + nr == h) break;
		for (int j = 0; j < w; ++j) {
			if (arr[i + nr][j] == '.') visit += (1ULL << idx[i + nr][j]);
		}
	}
	if (mp[nr][nc].find(visit) != mp[nr][nc].end()) {
			if (mp[nr][nc][visit] >= cnt) return;
		}
	mp[nr][nc][visit] = cnt;

	int nnr = nr, nnc = nc + 1;
	if (nnc == w) {
		++nnr;
		nnc = 0;
	}

	for (int b = 0; b < 4; ++b) {
		if (check(nr, nc, b)) {
			paint(nr, nc, b, '#');
			getRes(nnr, nnc, cnt + 1);
			paint(nr, nc, b, '.');
		}
	}
	getRes(nnr, nnc, cnt);
}

int main() {
	ios_base::sync_with_stdio(0), cout.tie(0), cin.tie(0);

	int cnt;
	cin >> cnt;

	while (cnt--) {
		cin >> h >> w >> r >> c;
		for (int i = 0; i < h; ++i) for(int j = 0; j < w; ++j) mp[i][j].clear();
		len = r < c ? c : r;
		best = 0;
		ilen = 0;

		for (int b = 0; b < 4; ++b) {
			for (int i = 0; i < r; ++i) for (int j = 0; j < c; ++j) block[b][i][j] = '.';
		}

		for (int i = 0; i < h; ++i) cin >> arr[i];
		for (int i = 0; i < h; ++i) {
			for (int j = 0; j < w; ++j) {
				if (arr[i][j] == '.') {
					idx[i][j] = ilen++;
				}
			}
		}
		for (int i = 0; i < r; ++i) {
			cin >> block[0][i];
		}

		for (int i = 0; i < len; ++i) {
			for (int j = 0; j < len; ++j) {
				if (i >= r || j >= c) block[0][i][j] = '.';
			}
		}
		rotate();
		getRes(0, 0, 0);
		cout << best << '\n';
	}
	return 0;
}
