#include<map>
#include<string>
#include<iostream>

using namespace std;

char arr[10][11];
int intmap[10][10];
int whiltes[100][2];
int wlen;
char block[4][10][11];
int h, w, r[4], c[4];
int cod[4][2];
map<string, int > se[100];

bool isout(int i, int j) {
	return i < 0 || j < 0 || i >= h || j >= w;
}

bool check(int x, int y, int b, int bnum) {
	for (int i = 0; i < r[b]; ++i) {
		for (int j = 0; j < c[b]; ++j) {
			if (isout(x + i, y + j) || block[b][i][ j] == '#' && arr[x + i][y + j] == '#') return false;
		}
	}
	return true;
}

void mark(int x, int y, int b, char ch, string &mk) {
	for (int i = 0; i < r[b]; ++i) {
		for (int j = 0; j < c[b]; ++j) {
			if (block[b][i][j] == '#')
			{
				arr[x + i][y + j] = ch;
				mk[intmap[x+i][y+j]] = '1';
			}
		}
	}
}

#define maxx(x,y) ((x) > (y) ? (x) : (y))

int dfs(int bnum, string visit) {
	if (bnum == wlen) return 0; 
	int x = whiltes[bnum][0];
	int y = whiltes[bnum][1];
	string mk;

	if (bnum) visit[bnum - 1] = '0';
    if (se[bnum].find(visit) != se[bnum].end()) return se[bnum][visit];

	for (int d = 0; d < 4; ++d) {
		if (block[d][cod[d][0]][cod[d][1]] == '#' && check(x- cod[d][0] , y -cod[d][1], d,bnum)) {
			mk = visit;
			mark(x-cod[d][0] , y - cod[d][1], d, '#',mk);
			se[bnum][visit] = maxx(se[bnum][visit], 1+dfs(bnum + 1, mk));
			mark(x-cod[d][0], y - cod[d][1],d, '.', mk);
		}
	}
	return se[bnum][visit] = maxx(se[bnum][visit], dfs(bnum+1,visit));
}

int main() {
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	int t;
	cin >> t;
	while (t--) {
		cin >> h >> w >> r[0] >> c[0];
		wlen = 0;

		for (int i = 0; i < h; ++i) {
			for (int j = 0; j < w; ++j) {
				cin >> arr[i][j];
				if (arr[i][j] == '.') {
					whiltes[wlen][0] = i, whiltes[wlen][1] = j;
					intmap[i][j] = wlen++;
				}
			}
		}

		for (int i = 0; i < r[0]; ++i) cin >> block[0][i];
		for (int i = 0; i < wlen; ++i) se[i].clear();

		for (int i = 1; i < 4; ++i) {
			r[i] = c[i - 1];
			c[i] = r[i - 1];

			for (int ii = 0; ii < r[i]; ++ii) {
				for (int j = 0; j < c[i]; ++j) {
					block[i][ii][j] = block[i - 1][c[i] - 1 - j][ii];
				}
			}
		}

		for (int d = 0; d < 4; ++d) {
			for (int i = 0; i < r[d]; ++i) for (int j = 0; j < c[d]; ++j) {
				if (block[d][i][j] == '#') {
					cod[d][0] = i, cod[d][1] = j;
					goto ENDLOOP;
				}
			}
		ENDLOOP:
			int x = 1;
		}
		string a;
		a.resize(wlen,'0');
		cout << dfs(0, a) << '\n';
	}
	return 0;
}
