#include<iostream>
#include<queue>

using namespace std;

int n, k, m, l;
int before[12];
int semester[10];
int visit[11][11][1 << 12];

struct NODE {
	int m, d,visit;
};

queue<NODE> Q;

#define MAX(x,y) ((x) > (y) ? (x) : (y))
#define MIN(x,y) ((x) > (y) ? (y) : (x))
int getcount(int bit) {
	int res = 0;
	while (bit) {
		res++;
		bit -= bit & -bit;
	}
	return res;
}

bool canget(int get, int now) {
	for (int i = 0; i < n; ++i) {
		if (get & (1 << i) && (before[i] & now) != before[i]) {
			return false;
		}
	}
	return true;
}

int main() {
	int tc=0;
	int q;
	scanf("%d", &q);

	while (q--) {
		tc++;
		for (int i = 0; i < n; ++i) before[i] = 0;
		for (int i = 0; i < m; ++i) semester[i] = 0;
		scanf("%d %d %d %d", &n, &k, &m, &l);
		
		for (int i = 0; i < n; ++i) {
			int r;
			scanf("%d", &r);
			while (r--) {
				int in;
				scanf("%d", &in);
				before[i] |= (1 << in);
			}
		}

		for (int i = 0; i < m; ++i) {
			int c;
			scanf("%d", &c);
			for (int j = 0; j < c; ++j) {
				int in;
				scanf("%d", &in);
				semester[i] |= 1 << in;
			}
		}

		Q.push({ 0,0,0 });
		visit[0][0][0] = tc;
		int res = 100;

		while (Q.size()) {
			NODE now = Q.front(); Q.pop();
			int cnt = getcount(now.visit);

			if (cnt >= k) {
				res = MIN(res, now.m);
				continue;
			}

			NODE next;
			int avail = 0;

			for (int get = semester[now.d]; get; get = (get - 1) & semester[now.d]) {
				if (l < getcount(get)) continue;
				next = now;
				next.d++;
				next.m++;
				next.visit |= get;
				if (next.d <= m&& canget(get, now.visit) && visit[next.m][next.d][next.visit]!=tc ) {
					visit[next.m][next.d][next.visit] = tc;
					Q.push(next);
				}
			}

			next = now;
			next.d++;
			if (next.d <= m && visit[next.m][next.d][next.visit] != tc) {
				visit[next.m][next.d][next.visit] = tc;
				Q.push(next);
			}
		}
		if (res == 100) printf("IMPOSSIBLE\n");
		else printf("%d\n", res);
	}
	return 0;
}