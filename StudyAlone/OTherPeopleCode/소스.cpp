#include< iostream >
#include< cstdio >
#include< vector >
#include< cstring >
#include< queue >
#include< algorithm >
#define R 1005

using namespace std;
typedef pair< int, int > pi;

int test, n, ans, dist[R];
bool chk[R][R], visit[R];
vector< int > adj[R], v;

int dfs(int pos, int cnt) { //2사이클 이하 값을 찾음.
	if (visit[pos]) {
		return cnt;
	}

	int mx = 0;
	visit[pos] = true;
	int a, b;
	a = b = 0;
	for (auto next : adj[pos]) {
		if (cnt == 0) {
			int t = dfs(next, cnt + 1);
			if (a > b) {
				b = max(b, t);
			}
			else {
				a = max(a, t);
			}
		}
		else mx = max(mx, dfs(next, cnt + 1));
	}

	if (cnt == 0) {
		if (a >0 && b >0) mx = a + b - 1;
		else mx = a + b;
	}
	return mx == 0 ? cnt + 1 : mx;
}

int dfs2(int pos, int cnt) { // 3사이클이상 값을 찾음.
	if (visit[pos]) {
		return cnt - dist[pos];
	}

	int mx = 0;
	visit[pos] = true;
	dist[pos] = cnt;
	for (auto next : adj[pos]) {
		mx = max(mx, dfs2(next, cnt + 1));
	}

	if (mx <= 0) {
		visit[pos] = false;
		dist[pos] = 0;
		return 0;
	}
	return mx;

}
int main() {

	scanf("%d", &test);

	for (int tc = 1; tc <= test; tc++) {
		scanf("%d", &n);

		memset(dist, 0, sizeof(dist));
		memset(chk, false, sizeof(chk));
		for (int i = 1; i <= n; i++) {
			int a;
			scanf("%d", &a);
			adj[a].push_back(i);
			chk[a][i] = true;
			if (chk[i][a]) v.push_back(i);
		}

		for (int j = 1; j <= n; j++) visit[j] = false;
		int ans = 0;

		while (!v.empty()) {
			int s = v.back();
			v.pop_back();
			if (visit[s]) continue;
			ans += dfs(s, 0);
		}

		int cnt = 0;
		for (int i = 1; i <= n; i++) {
			if (visit[i]) continue;
			int c = dfs2(i, 0);
			cnt = max(cnt, c);
		}

		ans = max(ans, cnt);
		printf("#%d %d\n", tc, ans);

		for (int i = 1; i <= n; i++) adj[i].clear();
	}


	return 0;
}