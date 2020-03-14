//Maximum White Subtree
#include<iostream>
#include<vector>

int n;
using namespace std;
vector<int> adj[200001];
int mycolor[200001];
int dp[200001];
int p[200001];
int Q[200001];

int getdp(int v){
    int &ret = dp[v];
    if(ret != 0x3f3f3f3f) return dp[v];
    ret = 0;
    for(int i = 0; i < adj[v].size(); ++i){
        int next = adj[v][i];
        if(next == p[v]) continue;
        ret += getdp(next);
    }
    ret += mycolor[v];
    return ret < 0 ? 0 : ret;
}

int dp2[200001];
void getdp2(int v){
    dp2[v] += dp[v];

    for(int i = 0; i < adj[v].size(); ++i){
        int next = adj[v][i];
        if(next == p[v]) continue;
        int up = dp2[v];
        if(dp[next] > 0) up -= dp[next];
        if(up > 0) dp2[next] += up;
        getdp2(next);
    }
}

int main(){
    freopen("0Text.txt", "r", stdin);
    int n;
    cin >> n;
    for(int i = 1; i <= n; ++i){
        int color ;
        cin >> color;
        if(color == 0) mycolor[i] = -1;
        else mycolor[i] = 1;
        dp[i] = 0x3f3f3f3f;
    }

    for(int i = 0; i < n-1; ++i){
        int f, t;
        cin >> f >> t;
        adj[f].push_back(t);
        adj[t].push_back(f);
    }
    int fr, re;
    fr = re = 0;
    Q[re++]= 1;
    p[1] = -1;
    while(fr != re){
        int now = Q[fr++];
        for(int i = 0; i < adj[now].size(); ++i){
            int next = adj[now][i];
            if(p[next]) continue;
            p[next] = now;
            Q[re++]= next;
        }
    }

    getdp(1);
    getdp2(1);
    
    for(int i = 1; i <= n; ++i){
        cout << dp2[i] << ' ';
    }

    return 0;
}