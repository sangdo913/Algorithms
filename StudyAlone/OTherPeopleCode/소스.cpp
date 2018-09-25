#include<iostream>
#include<queue>
#include<cstring>
const int QS = 6000000;
using namespace std;

int n;
int info[5011][5011];
int que[10000000];
int que2[2000];
bool collision[1001];

struct atom {
	int r, c, d, e;
} atoms[1011];

int dr[4] = { 1,-1,0,0 };
int dc[4] = { 0,0,-1,1 };

int main() {
	int t;
	cin >> t;

	for (int tc = 1; tc <= t; tc++) {
		cin >> n;

		int f, r;

		f = r = 0;

		for (int i = 1; i <= n; i++) {
			cin >> atoms[i].c >> atoms[i].r >> atoms[i].d >> atoms[i].e;

			atoms[i].c = atoms[i].c * 2 + 2000;
			atoms[i].r = atoms[i].r * 2 + 2000;

			que[r++] = i;
			collision[i] = false;
		}

		int res = 0;

		while (f != r) {
			int cnt = r - f;

			int f2, r2;
			f2 = r2 = 0;

			while (cnt--) {
				int i = que[f++];

				if (collision[i]) continue;

				int &d = atoms[i].d;

				atoms[i].r += dr[d];
				atoms[i].c += dc[d];

				if (atoms[i].r < 0 || atoms[i].r > 4000 || atoms[i].c < 0 || atoms[i].c > 4000) {
					atoms[i].e = 0;
					continue;
				}

				if (info[atoms[i].r][atoms[i].c]) {
					int boom = info[atoms[i].r][atoms[i].c];

					res += atoms[boom].e + atoms[i].e;
					collision[boom] = true;

					atoms[boom].e = 0;
					atoms[i].e = 0;
				}

				else{
					info[atoms[i].r][atoms[i].c] = i;
					que[r++] = i;
					que2[r2++] = i;
				}
			}

			while (r2 != f2) {
				int now = que2[f2++];
				info[atoms[now].r][atoms[now].c] = 0;
			}
		}
		cout << '#' << tc << ' ' << res << '\n';
	}
	return 0;
}