#include<iostream>

using namespace std;

int n;
bool map[20][20];
int x[500], y[500], sum[500], check[500];
int firstlen[500];
int len[500];
bool sero[500];
int arr[20][20];
int m;
int dr[2] = { 0,1 };
int dc[2] = { 1,0 };
int full;
int info[500][500];
int mapinfo[20][20];
int infolen[500];
int possible[1000];
int tc;
int complete[500];

int main() {
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cin >> tc;
	++tc;

	while (--tc) {
		full = 0;
		cin >> n;
		for (int i = 0; i < n; ++i) for (int j = 0; j < n; ++j) cin >> map[i][j], arr[i][j] = 0, full += map[i][j];
		cin >> m;
		firstlen[0] = 10000;
		len[0] = 10000;

		for (int i = 1; i <= m; ++i) {
			check[i] = 0;
			infolen[i] = 0;
			len[i] = 0;
			cin >> y[i] >> x[i] >> sero[i] >> sum[i];
			y[i] -= !sero[i], x[i] -= sero[i];
			int r = y[i];
			int c = x[i];
			while (r < n && c < n && map[r][c]) {
				len[i]++;
				info[i][infolen[i]++] = (r << 10) + c;
				mapinfo[r][c] |= i << (10*(int)sero[i]);
				r += dr[sero[i]], c += dc[sero[i]];
			}
			firstlen[i] = len[i];
		}

		int cnt = m;
		len[0] = 0x3f3f3f3f;
		while (cnt--) {
			int idx = 0;
			for (int i = 1; i <= m; ++i) {
				if (!len[i]) continue;
				if (len[idx] > len[i]) {
					idx = i;
				}
				else if (len[idx] == len[i] && sum[idx] > sum[i]) {
					idx = i;
				}
			}
			if (idx) {
				make(idx);
			}
		}

		for (int i = 0; i < n; ++i) {
			for (int j = 0; j < n; ++j) cout << arr[i][j] << ' ';
			cout << '\n';
		}
	}
	return 0;
}