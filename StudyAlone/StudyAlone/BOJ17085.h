#include<iostream>

using namespace std;

int n, m;
char arr[15][16];
int dr[] = { -1,1,0,0 };
int dc[] = { 0,0,-1,1 };

bool check(int r, int c, int len) {
	for (int d = 0; d < 4; ++d) {
		int tr = r+ dr[d],  tc = c +dc[d];
		for (int l = 0; l < len; ++l) {
			if (tr < 0 || tc < 0 || tr == n || tc == m || arr[tr][tc] !='#') return false;
			tr += dr[d];
			tc += dc[d];
		}
	}
	return true;
}

void point(int r, int c, int len, char ch) {
	arr[r][c] = ch;
	for (int d = 0; d < 4; ++d) {
		int tr = r+ dr[d],  tc = c +dc[d];
		for (int l = 0; l < len; ++l) {
			arr[tr][tc] = ch;
			tr += dr[d];
			tc += dc[d];
		}
	}
}

#define MAX(x,y) ((x) > (y) ? (x) : (y))

int dfs(int r, int c, int checked) {
	if (r == n) {
		return 0;
	}

	int nr = r, nc = c + 1;
	if (nc == m) nc = 0, nr++;

	int ret = 0;

	if (arr[r][c] == '#') {
		for (int i = 0; i <= 7; ++i) {
			if (check(r,c,i)) {
				if (checked) {
					ret = MAX(ret, checked * (4 * i + 1));
					continue;
				}
				point(r, c, i, '*');
				int temp = dfs(nr, nc, i * 4 + 1);
				ret = MAX(temp, ret);
				point(r, c, i, '#');
			}
			else break;
		}
	}
	int temp = dfs(nr, nc, checked);
	
	return MAX(temp,ret);
}

int main() {
	cin >> n >> m;
	for (int i = 0; i < n; ++i) cin >> arr[i];
	
	return !(cout << dfs(0, 0, 0));
	return 0;
}