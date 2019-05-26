#include<iostream>
#include<queue>

using namespace std;
int arr[15][15], n, m, range;
int pos[3];
int visit[15][15];
int query;
struct COD {
	int r, c;
};
COD que[100000];

bool operator<(const COD& a, const COD&b) {
	return a.c < b.c;
}

int dr[3] = { 0,0,-1 };
int dc[3] = { -1,1,0 };

int process() {
	int f, r;
	COD del[3];
	int dsize = 0;

	for (int i = 0; i < 3; ++i) {
		query++;
		f = r = 0;
		int nrange = 1;
		que[r].r = n - 1; 
		que[r++].c = pos[i];
		visit[n - 1][pos[i]] = query;

		priority_queue<COD> pq;

		while (f != r ) {
			int cnt = r - f;

			while (cnt--) {
				COD now = que[f++];

				for (int d = 0; d < 3; d++) {
					COD next = { now.r + dr[d], now.c + dc[d] };
					if (next.r < 0 || next.c < 0 || next.c == n) continue;
					if (visit[next.r][next.c] == query) continue;
					visit[next.r][next.c] = query;
				}
			}
			if (nrange++ == range) break;
			if (pq.size()) break;
		}

		if (pq.size()) del[dsize++] = pq.top();
	}
}

int getNum(int sel, int idx, int l, int r) {
	if (sel == 3 || r == 0) {
		return process();
	}
	if (l == r) {
		while (l--) pos[sel++] = idx++;
		return process();
	}

	pos[sel] = idx;
	int ret = 0;
	ret = getNum(sel+1, idx + 1, l - 1, r - 1);
	int ret2 = getNum(sel, idx + 1, l - 1, r);
	return ret > ret2 ? ret : ret2;
}

int main() {
	cin >> n >> m >> range;
	
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < m; ++j) {
			cin >> arr[i][j];
		}
	}
	return 0;
}