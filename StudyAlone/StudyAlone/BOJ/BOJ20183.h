#include<iostream>
#include<queue>
#include<algorithm>
#include<cmath>
#include<vector>
#include<cstring>
#include<tuple>

using namespace std;

vector<vector<pair<int,int>>>adj;
long long dist[100001];
int isin[100001];

int main() {
    freopen("0Text.txt", "r", stdin);
    int n , m, a, b;long long C;
    cin >> n >> m>> a>> b >> C;
    adj.resize(n+1);
    int tc = 0;
    while(m--) {
        int a, b, c;
        cin >> a >> b >> c;
        adj[a].push_back({b,c});
        adj[b].push_back({a,c});
    }
    int s = 0 , e = 1e9+1;
    while(s < e) {
        tc++;
        memset(dist,0x3f, sizeof(dist));
        dist[a] = 0;
        isin[a] = tc;
        int m = (s+e)/2;
        queue<int> pq;
        pq.push(a);
        bool find = false;
        while(pq.size()) {
            int f;long long c;
            f = pq.front();
            c = dist[f];
            isin[f] = 0;
            pq.pop();
            if(f == b) {
                find = true;
                break;
            }
            
            for(int i = 0; i < adj[f].size(); ++i) {
                int nxt = adj[f][i].first;
                int cost = adj[f][i].second;
                if(m >= cost){
                    if(dist[nxt] <= c + cost) continue;
                    if(c + cost > C) continue;
                    dist[nxt] = c+cost;
                    if(isin[nxt] == tc) continue;
                    pq.push(nxt);
                    isin[nxt] = tc;
                }
            }
        }
        if(!find) {
            s = m+1;
        }
        else e = m;
    }
    printf("%d\n", e == 1e9 + 1 ? -1 : e);
    
    return 0;
}