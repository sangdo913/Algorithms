#include<cstdio>
#include<vector>
#include<queue>
#include<vector>

using namespace std;

struct EDGE{
	int f, t, w;
};

int dist[501];

int edges[501][501][2];
vector<int> adj[501];
int len[501];
const int INF = 987654321;
int visit[501];
bool vis[501];
int n, m;

bool cango(){
    queue<int> que;
    que.push(1);
    vis[1] = true;
    bool res = false;

    while(que.size()){
        int now = que.front(); que.pop();
        if(visit[now] == n-1) res = true;

        for(int i = 0; i < adj[now].size(); i++){
            int next = adj[now][i];
            if(vis[next]) continue;
            vis[next] = true;

            que.push(next);
        }
    }
    return res; 
}

int Do() {
	scanf("%d %d\n", &n, &m);

	while(m--) {
		int from, to, cost;
		scanf("%d %d %d\n", &from, &to, &cost);
		edges[from][len[from]][0] = to;
		edges[from][len[from]++][1] = cost;
        adj[from].push_back(to);
	}
	bool update = true;

	for (int i = 1; i <= n; i++) dist[i] = 987654321;

	dist[1] = 0;
	for (int k = 0; k < n && update; k++) {
		update = false;
		for (int i = 1; i <= n; i++) {
			for (int j = 0; j < len[i]; j++) {
				int next = edges[i][j][0];
				int cost = dist[i] + edges[i][j][1];

				if (cost < dist[next]) {
					update = true;
                    visit[next] = k;
					dist[next] = cost;
                    
				}
			}
		}
	}

	if (cango() && update ) {
		printf("%d\n", -1);
	}
	else {
		for (int i = 2; i <= n; i++) {
			if (!vis[i]) printf("%d\n", -1);
			else printf("%d\n", dist[i]);
		}
	}
	return 0;
}