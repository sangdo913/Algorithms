//https://www.swexpertacademy.com/main/code/problem/problemDetail.do?contestProbId=AWXRFInKex8DFAUo
//SWEA 5648 ¿øÀÚ ¼Ò¸ê ½Ã¹Ä·¹ÀÌ¼Ç
#include<iostream>
#include<queue>
#include<cstring>

using namespace std;

int n;
int info[4001][4001];
int que[1000];
int que2[1000];

struct atom {
	int r, c, d, e;
} atoms[1011];

bool collision[1001];

int dr[4] = { 1,-1,0,0 };
int dc[4] = { 0,0,-1,1 };

int SWEA5648() {
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
			int cnt;
			if (f > r) {
				cnt = 1000 + r%1000 - f%1000;
			}
			else {
				cnt = r - f;
			}

			int f2, r2;
			f2 = r2 = 0;

			while (cnt--) {
				int i = que[f++%1000];
				atom &at = atoms[i];

				if (collision[i]) continue;

				int &d = at.d;

				at.r += dr[d];
				at.c += dc[d];

				if(at.r < 0 || at.r > 4000 || at.c < 0 || at.c > 4000){
					at.e = 0;
					continue;
				}

				if (info[at.r][at.c]) {
					int boom = info[at.r][at.c];
					collision[boom] = true;
				}

				else {
					info[at.r][at.c] = i;
					que[r++%1000] = i;
					que2[r2++] = i;
				}
			}

			while (r2 != f2) {
				int now = que2[f2++];
				info[atoms[now].r][atoms[now].c] = 0;
			}
		}
		for (int i = 1; i <= n; i++) res += atoms[i].e;
		cout << '#' << tc << ' ' << res << '\n';
	}
	return 0;
}