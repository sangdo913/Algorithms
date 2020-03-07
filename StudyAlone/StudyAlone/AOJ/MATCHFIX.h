#include<iostream>
#include<queue>
#include<cstring>
#define MIN(x,y) ((x) > (y) ? (y) : (x))
#define INF 0x3f3f3f3f

using namespace std;


int f[120][120];
int c[120][120];
int parent[120];
int adj[120][2];
int alen[120];
int win[12];
int s, t;
int n, m;
int matchnum;
int flow;

bool networkflow(int dst){
    for(int i = 1; i < n; ++i){
        if(dst -1 < win[i]) return false;
        c[i][t] = dst-win[i]-1;
        c[t][i] = 0;
    }
    c[0][t] = dst - win[0];
    c[t][0] = 0;

    while(true){
        queue<int> Q;
        for(int i = 0; i <= t; ++i) parent[i] = -1;
        parent[s] = s;
        Q.push(s);
        while(!Q.empty()){
            int here = Q.front(); Q.pop();
            if(here == t) break;
            for(int i = 0; i <= t; ++i){
                int next = i;
                if(next == here) continue;
                if(parent[next] != -1) continue;
                if(c[here][next] > f[here][next]){
                    parent[next] = here;
                    Q.push(next);
                }
            }
        }
        if(parent[t] == -1) break;
        int here = t;
        int minflow = INF;
        while(here != s ){
           minflow = MIN(minflow, c[parent[here]][here] - f[parent[here]][here]); 
           here = parent[here];
        }
        here = t;
        while(here != s){
            f[parent[here]][here] += minflow;
            f[here][parent[here]] -= minflow;
            here = parent[here];
        }
        flow += minflow;
    }
    if(f[0][t] + win[0] != dst) return false;

    return flow == m;
}

int bs(){
    flow = 0;
    for(int i = win[0]; i <= win[0] + m; ++i){
        if(networkflow(i)) return i;
    }
    return -1;
}

int main(){
    ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);

    freopen("0Text.txt", "r", stdin);

    int C;
    cin >> C;
    while(C--){
        cin >> n >> m;
        memset(c,0,sizeof(c));
        memset(f,0,sizeof(f));
        s = n + m;
        t = s+1;
        matchnum = m;

        for(int i = 0;i < n; ++i) {
            cin >> win[i];
            adj[i][0] = t;
            alen[i] = 1;
        }
        for(int i = 0; i < m; ++i){
            int a, b;
            cin >> a >> b;
            if(b < a){
                a^=b^=a^=b;
            }
            c[n+i][a] = 1;
            c[n+i][b] = 1;
            c[s][n+i] = 1;
            adj[n+i][0] = a, adj[n+i][1] = b;
            alen[n+i] = 2;
            adj[s][i] = n+i;
            c[s][n+i] = 1;
        }
        alen[s] = m;
        int res = bs();
        cout << res << '\n';
    }
    return 0;
}