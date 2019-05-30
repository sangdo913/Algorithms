#include<iostream>
#include<queue>

using namespace std;
int arr[16][15], n, m, range;
int temp[16][15];
int pos[3];
int visit[16][15];
int query;
struct COD {
	int r, c;
};
COD que[100000];

bool operator<(const COD& a, const COD&b) {
	return a.c > b.c;
}

int dr[3] = { 0,0,-1 };
int dc[3] = { -1,1,0 };

int process() {
	int f, r;
	int ret = 0;

	for (int i = 0; i < n; ++i) for (int j = 0; j < m; ++j) {
		temp[i][j] = arr[i][j];
	}
	int delsize;
	COD del[3];

	for (int cnt = 0; cnt < n; ++cnt) {
		delsize = 0;
		for (int i = 0; i < 3; ++i) {
			query++;
			f = r = 0;
			int nrange = 0;
			que[r].r = n;
			que[r++].c = pos[i];

			priority_queue<COD> pq;

			while (f != r) {
				int cnt = r - f;

				while (cnt--) {
					COD now = que[f++];
					if (temp[now.r][now.c]) pq.push(now);

					for (int d = 0; d < 3; d++) {
						COD next = { now.r + dr[d], now.c + dc[d] };
						if (next.r < 0 || next.c < 0 || next.c >= m || next.r >= n) continue;
						if (visit[next.r][next.c] == query) continue;
						visit[next.r][next.c] = query;

						que[r++] = next;
					}
				}

				if (nrange++ == range) break;
				if (pq.size()) break;
			}

			if (pq.size()) {
				del[delsize++] = pq.top();
			}

		}

		for (int i = 0; i < delsize; ++i) {
			int r = del[i].r;
			int c = del[i].c;

			if (temp[r][c]) ret++;
			temp[r][c] = 0;
		}

		for (int i = n - 1; i; --i) {
			for (int j = 0; j < m; ++j) {
				temp[i][j] = temp[i - 1][j];
			}
		}
		for (int j = 0; j < m; ++j) temp[0][j] = 0;

	}
	return ret;
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
	ret = getNum(sel + 1, idx + 1, l - 1, r - 1);
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

	cout << getNum(0, 0, m, 3) << '\n';
	return 0;
}