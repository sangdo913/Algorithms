#include<iostream>
#include<queue>
#include<algorithm>
#include<vector>

using namespace std;

int dist[2][100001];
vector<int> adj[100001];
vector<int> cost[100001];

int main(){
    // freopen("0Text.txt", "r", stdin);
    ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);

    int n, d;
    cin >> n >> d;

    while(d--){
        int f,t, c;
        cin >> f >> t >> c;
        adj[f].push_back(t);
        cost[f].push_back(c);
        adj[t].push_back(f);
        cost[t].push_back(c);
    }
    for(int i =1; i <= n; ++i){
        dist[0][i] = dist[1][i] = 0x3f3f3f3f;
    }

    priority_queue<pair<int, int>> pq;
    pq.push({0,1});
    dist[0][1] = 0;

    while(!pq.empty()){
        pair<int, int> now = pq.top(); pq.pop();
        int c = -now.first;
        int ni = now.second;
        if(c > dist[1][ni]) continue;

        for(int i = 0; i < adj[ni].size(); ++i){
            int nn = adj[ni][i];
            int nc = c + cost[ni][i];

            if(dist[0][nn] > nc){
                dist[1][nn] = dist[0][nn];
                dist[0][nn] = nc;
                pq.push({-nc, nn});
            }
            else if(dist[0][nn] != nc && dist[1][nn] > nc){
                dist[1][nn] = nc;
                pq.push({-nc,nn});
            }
        }
    }
    cout << dist[1][n];

    return 0;
}