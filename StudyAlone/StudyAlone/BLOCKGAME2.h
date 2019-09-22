#include<cstdio>
#include<map>
#include<iostream>
#include<cstdlib>

using namespace std;
typedef long long ll;


char arr[10][11];
int intmap[10][10];
char block[4][10][10];
int h, w, r[4], c[4];
map<ll, int> se[10][10];

bool isout(int i, int j) {
	return i < 0 || j < 0 || i >= h || j >= w;
}

bool check(int x, int y, int b) {
	for (int i = 0; i < r[b]; ++i) {
		for (int j = 0; j < c[b]; ++j) {
			if (isout(x + i, y + j) || block[b][x + i][y + j] == '#' && arr[x + i][y + j] == '#') return false;
		}
	}
	return true;
}

ll mark(int x, int y, int b, char ch) {
	ll mk = 0;
	for (int i = 0; i < r[b]; ++i) {
		for (int j = 0; j < c[b]; ++j) {
			if (block[b][x + i][y + j] == '#')
			{
				block[b][x + i][y + j] = ch;
				mk |= (1LL << intmap[x + i][y + j]);
			}
		}
	}
	return mk;
}

#define maxx(x,y) ((x) > (y) ? (x) : (y))

int dfs(int r, int c, int num, ll mapinfo) {
	if (se[r][c].find(mapinfo) != se[r][c].end()) {
		return se[r][c][mapinfo] + num;
	}
	if (r == h) return 0;

	int nr = r, nc = c + 1;
	ll mk;

	if (c + 1 == w) {
		nr++, nc = 0;
	}


	for (int d = 0; d < 4; ++d) {
		if (check(r, c, d)) {
			mk = mark(r, c, d, '#');
			mk |= mapinfo;
			se[r][c][mapinfo] = maxx(se[r][c][mapinfo], num + dfs(nr, nc, num + 1, mk));
		}
	}

	return se[r][c][mapinfo] = maxx(se[r][c][mapinfo], num + dfs(nr, nc, num, mk));
}


int main() {
	int t;
	scanf("%d ", &t);
	while (t--) {

		scanf("%d %d %d  %d ", &h, &w, r, c);
		int cnt = 0;

		for (int i = 0; i < h; ++i) {
			for (int j = 0; j < w; ++j) {
				se[i][j].clear();
				scanf("%c ", arr[i] + j);
				if (arr[i][j] == '.') {
					intmap[i][j] = cnt++;
				}
			}
		}
		for (int i = 0; i < r[0]; ++i) scanf("%s ", block[0][i]);

		for (int i = 1; i < 4; ++i) {
			r[i] = c[i - 1];
			c[i] = r[i - 1];

			for (int ii = 0; ii < r[i]; ++ii) {
				for (int j = 0; j < c[i]; ++j) {
					block[i][ii][j] = block[i - 1][c[i] - 1 - j][ii];
				}
			}
		}
	}
	return 0;
}