#include<iostream>

using namespace std;

struct INFO {
	int from;
	int sum;
};

INFO que1[10000];
int que2[5000], fr1, re1, fr2, re2;

int arr[50][50];

int dr[4] = { -1,0,1,0 };
int dc[4] = { 0,1,0,-1 };

bool inque[50][50];

int n, m, k;

bool isout(int r, int c, int r1, int r2, int c1, int c2){
	return r < r1 || r == r2 || c < c1 || c == c2;
}

int ar, ac, br, bc;

void move(int r, int c, bool isdown) {
	int nr = r, nc = c;
	int d = isdown * 2;
	int nnr, nnc;
	int sr = isdown * r;
	int er = isdown ? n : r+1;

	nnr = nr + dr[d], nnc = nc + dc[d];

	while (nnr != r || nnc != c) {
		if (arr[nr][nc] != -1) {
			arr[nr][nc] = arr[nnr][nnc];
		}

		nr = nnr, nc = nnc;
		nnr = nnr + dr[d];
		nnc = nnc + dc[d];

		if (isout(nnr, nnc, sr, er,0,m)) {
			d += 1 + isdown * 2;
			d %= 4;
			nnr = nr + dr[d];
			nnc = nc + dc[d];
		}
	}
	arr[nr][nc] = 0;
}

int ain() {
	int tt;
	cin >> n >> m >> k;
	bool isup = false;

	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < m; ++j) {
			cin >> arr[i][j];
				if (arr[i][j] == -1) {
					if (!isup) {
						isup = true;
						ar = i, ac = j;
					}
					else {
						br = i; bc = j;
					}
				}
		}
	}

	while (k--) {
		for (int i = 0; i < n; ++i) {
			for (int j = 0; j < m; ++j) {
				if (arr[i][j] > 0) {
					que1[(re1 % 10000)].from = i * m + j;
					que1[re1++ % 10000].sum = arr[i][j];
				}
			}
		}

		while (fr1 % 10000 != re1 % 10000) {
			INFO now = que1[(fr1++ % 10000)];
			int nr = now.from / m;
			int nc = now.from %m;

			for (int d = 0; d < 4; ++d) {
				int nnr = nr + dr[d];
				int nnc = nc + dc[d];

				if (!isout(nnr, nnc,0,n,0,m) && arr[nnr][nnc] != -1) {
					arr[nnr][nnc] += now.sum / 5;
					arr[nr][nc] -= now.sum / 5;
				}
			}
		}

		move(ar, ac, false);
		move(br, bc, true);
	}

	int res = 0;
	for (int i = 0; i < n; ++i) for (int j = 0; j < m; ++j) {
		res += arr[i][j] > 0 ? arr[i][j] : 0;
	}

	cout << res;

	return 0;
}
