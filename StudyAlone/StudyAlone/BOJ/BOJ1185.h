#include<iostream>
#include<algorithm>
#include<tuple>
#include<vector>

using namespace std;

vector<tuple<int, int, int>> edge;
int costs[10001];
int parent[10001];

int findp(int i){
    if(parent[i] < 0) return i;
    return findp(parent[i]);
}

void join(int a, int b){
    int pa = findp(a);
    int pb = findp(b);
    if(parent[pa] < parent[pb]) pa^=pb^=pa^=pb;
    parent[pb] += parent[pa];
    parent[pa] = pb;
}

int main(){
    freopen("0Text.txt", "r", stdin);
    int n, m;
    cin >> n >> m;
    int res = 0x3f3f3f3f;
    for(int i = 1; i <= n; ++i) parent[i] = -1;
    for(int i = 1; i <= n; ++i) {
        cin >> costs[i];
        if(costs[i] < res) res = costs[i];
    }
    edge.resize(m);
    for(int i = 0; i < m; ++i){
        int f, t, c;
        cin >> f >> t>>c;
        edge[i] = {2*c+costs[f]+costs[t],f,t};
    }
    sort(edge.begin(), edge.end());
    for(int i = 0; i < m; ++i){
        int c, f, t;
        tie(c,f,t) = edge[i];
        int pf = findp(f);
        int pt = findp(t);
        if(pf == pt) continue;
        join(pf, pt);
        res += c;
    }
    cout << res;

    return 0;
}