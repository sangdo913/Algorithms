#include<iostream>
#include<algorithm>
#include<vector>
#include<queue>
using namespace std;

vector<vector<int>> visit;
vector<vector<int>> adj;

int infect(int h) {
    if(visit[h].size() == 0){
        int ret = 0;
        for(int i = 0; i < h; ++i) ret += visit[i].size();
        return ret-h;
    }
    int ret = 0x3f3f3f3f;

    for(int i = 0 ; i < visit[h].size(); ++i){
        visit[h+1].clear();
        for(int j = 0; j < visit[h].size(); ++j){
            if(i == j) continue;
            int now = visit[h][j];
            for(int ii = 0;ii< adj[now].size(); ++ii){
                int nxt = adj[now][ii];
                visit[h+1].push_back(nxt);
            }
        }
        ret = min(ret, infect(h+1));
    }
    return ret;
}

int solution(int n, vector<vector<int>> edges){
    visit.clear();
    visit.resize(n+1);

    adj.clear();
    adj.resize(n);

    for(int i = 0; i < edges.size(); ++i){
        int f = edges[i][0];
        int t = edges[i][1];
        adj[f].push_back(t);
    }
    visit[0].push_back(0);
    visit[0].push_back(0);
    return infect(0);
}

int main() {
    freopen("0Text.txt", "r", stdin);
    int n;
    vector<int> v;
    vector<vector<int>> edges;
    int m;
    cin >> n;
    for(int i = 0; i < n-1; ++i){
        int f,t;
        cin >> f >> t;
        edges.push_back({f,t});
    }
    cout << solution(n,edges);

    return 0;
}