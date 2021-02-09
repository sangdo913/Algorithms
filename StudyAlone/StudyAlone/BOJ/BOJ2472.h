#include<iostream>
#include<cstring>
#include<queue>
#include<vector>
#include<algorithm>
using namespace std;

int fenwick[100001*5];
int dist[3][100001];
int info[3][100001];
vector<int> alldist;
int inQ[100001];
vector<int> adj[100001];
vector<int> cost[100001];
int cantbuild[100001];

struct cmp{
    bool operator()(int a, int b){
        return dist[0][a] < dist[0][b];
    }
};

int main(){
    ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    freopen("0Text.txt" ,"r", stdin);
    int n ;
    cin >> n;
    int st[3];
    cin >> st[0] >> st[1] >> st[2];
    int m;
    cin >> m;
    while(m--) {
        int x,y,z;
        cin >> x >> y >> z;
        adj[x].push_back(y);
        adj[y].push_back(x);
        cost[x].push_back(z);
        cost[y].push_back(z);
    }
    memset(dist, 0x3f, sizeof(dist));
    queue<int>Q;
    for(int i = 0; i < 3; ++i) {
        priority_queue<pair<int,int>> pq;
        pq.push({0,st[i]});
        // dist[i][st[i]] = 0;
        // inQ[st[i]] = 1;
        while(pq.size()) {
            auto [d,now] = pq.top(); pq.pop();
            if(inQ[now] == i + 1) continue;
            inQ[now] = i+1;
            d = -d;
            dist[i][now] = d;
            // cout << now << ' ' << d << endl;
            // inQ[now] = 0;
            for(int j = 0; j < adj[now].size(); ++j){
                int nxt = adj[now][j];
                if(inQ[nxt] != i + 1) {
                    pq.push({-(d+ cost[now][j]), nxt});
                }
                // if(d + cost[now][j] < dist[i][nxt]){
                //     dist[i][nxt] = dist[i][now] + cost[now][j];
                //     if(!inQ[nxt]){
                //         inQ[nxt] = 1;
                //         Q.push(nxt);
                //     }
                // }
            }
        }
    }
    for(int i = 0; i < 3; ++i){
        for(int j = 1; j <= n; ++j){
            alldist.push_back(dist[i][j]);
            // cout << dist[i][j] << ' ';
        }
        // cout << endl;
    }
    // cout << endl;

    sort(alldist.begin(), alldist.end());
    alldist.resize(unique(alldist.begin(), alldist.end())-alldist.begin());
    for(int i = 0; i < 3; ++i) {
        for(int j = 1; j <= n; ++j) {
            dist[i][j] = lower_bound(alldist.begin(), alldist.end(), dist[i][j]) - alldist.begin()+1;
        }
    }
    vector<int> order;
    for(int i = 1; i <= n; ++i) order.push_back(i);
    sort(order.begin(), order.end(), cmp());
    // for(int i = 0; i < order.size(); ++i){
    //     cout << order[i] << ' ';
    // }
    // cout << endl;
    int prev = -1;
    int size = alldist.size();
    for(int i = 0; i <= size; ++i) fenwick[i] = 0x3f3f3f3f;
    for(int i = 0; i < order.size();) {
        int st = i;
        prev = dist[0][order[i]];
        while(i < order.size() && prev == dist[0][order[i]]) ++i;
        for(int j = st; j < i; ++j ) {
            int idx = dist[1][order[j]] - 1;
            int v = 0x3f3f3f3f;
            while(idx) {
                v = min(v, fenwick[idx]);
                idx -= idx & -idx;
            }
            if(dist[2][order[j]] < v) {
                // idx = dist[1][order[j]];
                // while(idx <= n) {
                //     fenwick[idx] = min(fenwick[idx], dist[2][order[i]]);
                //     idx += idx & -idx;
                // }
                Q.push(order[j]);
            }
            else cantbuild[order[j]] = 1;
        }
        while(Q.size()){
            int now = Q.front(); Q.pop();
            int idx = dist[1][now];
            while(idx <= size){
                fenwick[idx] = min(fenwick[idx], dist[2][now]);
                idx += idx & -idx;
            }
        }
    }
    // for(int i = 1; i<= n; ++i){
    //     cout << cantbuild[i] << ' ';
    // }
    int query = 0;
    cin >>query;
    while(query--){
        int now ;
        cin >> now;
        if(cantbuild[now]) cout <<"NO\n";
        else cout <<"YES\n";
    }

    return 0;
}