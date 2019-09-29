#include<iostream>
#define SIZE 20000
using namespace std;

int n,m,k;

int dr[5] = {0, -1,1,0,0 };
int dc[5] = {0, 0,0,1,-1 };
int conv[5] = { 0,2,1,4,3 };
int mod[5];

struct SHARK {
	int s,d,z;
	bool live;
}sharks[10001];

int arr[2][101][101];
int que[SIZE],fr,re;

int getshark(int c, int t) {
	for (int i = 0; i < n; ++i) { 
		if (arr[t][i][c]) {
			sharks[arr[t][i][c]].live = false;
			int ret = sharks[arr[t][i][c]].z;
			arr[t][i][c] = 0;
			return ret;
		}
	}
	return 0;
}

bool isout(int r, int c) {
	return r < 0 || c < 0 || r == n || c == m;
}

void move(int &r, int &c, int cnt, int &d){
	while(cnt--){
		int nr = r + dr[d], nc = c + dc[d];
		if(isout(nr,nc)){
			d = conv[d];
			nr = r + dr[d];
			nc = c + dc[d];
		}
		r = nr, c = nc;
	}
}

int Do() {
	cin >> n >> m >> k;
	mod[1] = mod[2] = 2*n-2;
	mod[3] = mod[4] = 2*m-2;
	
	for (int i = 1; i <= k; ++i) {
		int r, c, s, d, z;
		cin >> r >> c >> s >> d >> z;
		
		que[re++] = --r * m + --c;
		arr[0][r][c] = i;

		sharks[i].s = s;
		sharks[i].d = d;
		sharks[i].z = z;
		sharks[i].live = true;
	}

	int res = 0;
	for (int king = 0; king < m; king++) {
		res += getshark(king, king%2);

		int cnt = (re%SIZE + SIZE - fr%SIZE)%SIZE;

		while (cnt--) {
			int nr = que[fr%SIZE] / m;
			int nc = que[fr++%SIZE] % m;

			int sid = arr[king%2][nr][nc];
			arr[king % 2][nr][nc] = 0;
			int d = sharks[sid].d;

			if (sharks[sid].live){
				int mcnt = sharks[sid].s;
				if(sharks[sid].s >= mod[d]){
					move(nr,nc,mod[d], sharks[sid].d);
					mcnt -= mod[d];
				}

				mcnt = mcnt%mod[d];
				move(nr,nc, mcnt, sharks[sid].d);

				int si2 = arr[(king + 1) % 2][nr][nc];
				
				if (si2) {
					if (sharks[sid].z > sharks[si2].z) {
						sharks[si2].live = false;
						arr[(king + 1) % 2][nr][nc] = sid;
					}
				}
				else arr[(king + 1) % 2][nr][nc] = sid, que[re++%SIZE] = nr * m + nc;
			}
		}
	}
	cout << res;

	return 0;
}