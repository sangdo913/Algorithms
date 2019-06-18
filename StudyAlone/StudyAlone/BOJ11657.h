//#include<cstdio>
//
//using namespace std;
//
//int dist[501];
//
//int edges[501][501][2];
//int len[501];
//const int INF = 987654321;
//int visit[501];
//bool inque[501];
//int adj[501][501];
//int n, m;
//int Q[501 * 6000];
//
//int main() {
//	scanf("%d %d\n", &n, &m);
//
//	for (int i = 1; i <= n; ++i) for (int j = 1; j <= n; ++j) adj[i][j] = -1;
//	while(m--) {
//		int from, to, cost;
//		scanf("%d %d %d\n", &from, &to, &cost);
//
//		if (adj[from][to] == -1) {
//			adj[from][to] = len[from];
//			edges[from][len[from]][0] = to;
//			edges[from][len[from]++][1] = cost;
//		}
//		else {
//			int idx = adj[from][to];
//			edges[from][idx][1] = edges[from][idx][1] < cost ? edges[from][idx][1] : cost;
//		}
//	}
//
//	for (int i = 2; i <= n; i++) dist[i] = 987654321;
//	int fr = 0, re = 0;
//	Q[re++] = 1;
//
//	while (fr!=re) {
//		int now = Q[fr++];
//		inque[now] = false;
//
//		visit[now]++;
//		if (visit[now] == n) return!printf("-1");
//
//		for (int i = 0; i < len[now]; ++i) {
//			int next = edges[now][i][0];
//			int nd = dist[now] + edges[now][i][1];
//
//			if (dist[next] > nd) {
//				dist[next] = nd;
//				if (!inque[next]) Q[re++] = next, inque[next] = true;
//			}
//		}
//	}
//
//	for (int i = 2; i <= n; ++i) {
//		printf("%d\n", dist[i] != INF ? dist[i] : -1);
//	}
//	
//	return 0;
//}

#include<cstdio>

int edges[501][6000][2];
int len[501];
int dist[501];

int main() {
	int n, m, from, to, cost, nd;

	scanf("%d %d ", &n, &m);
	for (int i = 1; i <= n; ++i) dist[i] = 0x3f3f3f3f;

	while (m--) {
		scanf("%d %d %d ", &from, &to, &cost);
		edges[from][len[from]][0] = to;
		edges[from][len[from]++][1] = cost;
	}

	dist[1] = 0;

	for (int i = 0; i < n; ++i) {
		for (int fr = 1; fr <= n ; ++fr ){
			if (dist[fr] == 0x3f3f3f3f) continue;
			
			for (int eid = 0; eid < len[fr]; ++eid) {
				nd = dist[fr] + edges[fr][eid][1];

				if (dist[edges[fr][eid][0]] > nd) {
					if (i == n - 1) return !printf("-1");
					dist[edges[fr][eid][0]] = nd;
				}
			}
		}
	}

	for (int i = 2; i <= n; ++i) 
		if(dist[i] == 0x3f3f3f3f)printf("-1\n"); 
		else printf("%d\n", dist[i]);

	return 0;
}