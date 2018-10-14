#include<iostream>
#include<cstring>

using namespace std;

int n, m;
int map[101][101];

int dr[4] = { -1,1,0,0 };
int dc[4] = { 0,0,-1,1 };

int A[2][2];
int B[2][2];

int que[11000][2];

int dist = 0x3f3f3f3f;
int MIN(int i1, int i2) { return i1 < i2 ? i1 : i2; }

bool visit[101][101] = {};
void bfs(int r, int c, int der, int dec ,int len1) {
	visit[r][c] = true;
	int s = 0, e = 0;
	
	que[e][0] = r;
	que[e++][1] = c;
	int len = 0;
	bool find = false;

	while (s != e && !find) {
		int cnt = e - s;
		while (cnt-- && !find) {
			int now[2] = { que[s][0], que[s++][1] };

			if (now[0] == der && now[1] == dec) {
				find = true;  break;
			}

			for (int d = 0; d < 4; d++) {
				int next[2];
				next[0] = now[0] + dr[d];
				next[1] = now[1] + dc[d];

				if (next[0] < 0 || next[1] < 0 || next[0] > m || next[1] > n) continue;
				if (visit[next[0]][next[1]]) continue;
				visit[next[0]][next[1]] = true;

				que[e][0] = next[0];
				que[e++][1] = next[1];
			}
		}
		if (find) break;
		len++;
	}

	if (find) {
		dist = MIN(dist, len1 + len);
	}
}

int ABS(int i1) { return i1 > 0 ? i1 : -i1; }

void check(int f[2], int t[2], int f2[2], int t2[2]) {
	int len = 0;
	int dr = f[0] > t[0] ? -1 : 1;
	int dc = f[1] > t[1] ? -1 : 1;

	memset(visit, false, sizeof(visit));

	int now[2] = { f[0], f[1] };

	while (now[0] != t[0]) {
		len++;
		visit[now[0]][now[1]] = true;
		now[0] += dr;
	}
	while (now[1] != t[1]) {
		len++;
		visit[now[0]][now[1]] = true;
		now[1] += dc;
	}
	visit[now[0]][now[1]] = true;

	if(visit[f2[0]][f2[1]] == 0 && visit[t2[0]][t2[1]] ==0 )bfs(f2[0], f2[1], t2[0], t2[1],len);
}

void check2(int f[2], int t[2], int f2[2], int t2[2]) {
	int len = 0;
	int dr = f[0] > t[0] ? -1 : 1;
	int dc = f[1] > t[1] ? -1 : 1;
	dr = f[0] - t[0] ? dr : 0;
	dc = f[1] - t[1] ? dc : 0;

	memset(visit, false, sizeof(visit));

	int now[2] = { f[0], f[1] };

	visit[now[0]][now[1]] = true;
	len = 1;
	now[1] += dc;

	while (now[0] != t[0]) {
		len++;
		visit[now[0]][now[1]] = true;
		now[0] += dr;
	}
	while (now[1] != t[1]) {
		len++;
		visit[now[0]][now[1]] = true;
		now[1] += dc;
	}
	visit[now[0]][now[1]] = true;

	if (visit[f2[0]][f2[1]] == 0 && visit[t2[0]][t2[1]] == 0)bfs(f2[0], f2[1], t2[0], t2[1], len);
}

void check3(const int f[2], const int t[2], int f2[2], int t2[2]) {

	memset(visit, false, sizeof(visit));

	int now[2] = { f[0], f[1] };
	int len = 0;
	visit[now[0]][now[1]] = true;
	len = 1;
	now[1] -= 1;
	int dr = now[0] > t[0] ? -1 : 1;
	int dc = now[1] > t[1] ? -1 : 1;
	dr = now[0] - t[0] ? dr : 0;
	dc = now[1] - t[1] ? dc : 0;


	while (now[0] != t[0]) {
		len++;
		visit[now[0]][now[1]] = true;
		now[0] += dr;
	}
	while (now[1] != t[1]) {
		len++;
		visit[now[0]][now[1]] = true;
		now[1] += dc;
	}
	visit[now[0]][now[1]] = true;

	if (visit[f2[0]][f2[1]] == 0 && visit[t2[0]][t2[1]] == 0)bfs(f2[0], f2[1], t2[0], t2[1], len);
}
void check4(const int f[2], const int t[2], int f2[2], int t2[2]) {
	memset(visit, false, sizeof(visit));


	int len = 0;
	int now[2] = { f[0], f[1] };

	visit[now[0]][now[1]] = true;
	len = 1;
	now[0] -= 1;
;
	int dr = now[0] > t[0] ? -1 : 1;
	int dc = now[1] > t[1] ? -1 : 1;
	dr = now[0] - t[0] ? dr : 0;
	dc = now[1] - t[1] ? dc : 0;

	while (now[1] != t[1]) {
		len++;
		visit[now[0]][now[1]] = true;
		now[1] += dc;
	}

	while (now[0] != t[0]) {
		len++;
		visit[now[0]][now[1]] = true;
		now[0] += dr;
	}
	visit[now[0]][now[1]] = true;

	if (visit[f2[0]][f2[1]] == 0 && visit[t2[0]][t2[1]] == 0)bfs(f2[0], f2[1], t2[0], t2[1], len);
}
void check5(int f[2], int t[2], int f2[2], int t2[2]) {
	int len = 0;
	int dr = f[0] > t[0] ? -1 : 1;
	int dc = f[1] > t[1] ? -1 : 1;
	dr = f[0] - t[0] ? dr : 0;
	dc = f[1] - t[1] ? dc : 0;

	memset(visit, false, sizeof(visit));

	int now[2] = { f[0], f[1] };

	visit[now[0]][now[1]] = true;
	len = 1;
	now[0] += dr;


	while (now[1] != t[1]) {
		len++;
		visit[now[0]][now[1]] = true;
		now[1] += dc;
	}
	while (now[0] != t[0]) {
		len++;
		visit[now[0]][now[1]] = true;
		now[0] += dr;
	}

	visit[now[0]][now[1]] = true;

	if (visit[f2[0]][f2[1]] == 0 && visit[t2[0]][t2[1]] == 0)bfs(f2[0], f2[1], t2[0], t2[1], len);
}
int BOJ5022() {
	cin >> n >> m;

	cin >> A[0][1] >> A[0][0] >> A[1][1] >> A[1][0] >> B[0][1] >> B[0][0] >> B[1][1] >> B[1][0];
	
	check(A[0], A[1], B[0], B[1]);
	check(A[1], A[0], B[0], B[1]);
	check(B[0], B[1], A[0], A[1]);
	check(B[1], B[0], A[0], A[1]);
	check2(A[0], A[1], B[0], B[1]);
	check2(A[1], A[0], B[0], B[1]);
	check2(B[0], B[1], A[0], A[1]);
	check2(B[1], B[0], A[0], A[1]);	
	
	check5(A[0], A[1], B[0], B[1]);
	check5(A[1], A[0], B[0], B[1]);
	check5(B[0], B[1], A[0], A[1]);
	check5(B[1], B[0], A[0], A[1]);
	if (A[0][1] > 0) check3(A[0], A[1], B[0], B[1]);
	if (A[0][0] > 0) check4(A[0], A[1], B[0], B[1]);
	

	if (dist == 0x3f3f3f3f) {
		cout << "IMPOSSIBLE\n";
	}
	else {
		cout << dist << '\n';
	}

	return 0;
}