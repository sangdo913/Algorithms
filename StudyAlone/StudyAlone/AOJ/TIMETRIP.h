#include<iostream>
#include<queue>
#define OVERHEAD 1000000

using namespace std;
int adj[1000][1000];
int W[1000][1000];
int dist[1000];
int alen[1000];
int cycle[1000];
int inQ[1000];
int tc;

void go(int v){
    tc++;
    queue<int> Q;
    
    for(int i = 0; i < v; ++i) Q.push(i);
    dist[0] = 0;

    while(!Q.empty()){
        int cnt = Q.size();
        
        while(cnt--){
            int now = Q.front(); Q.pop(); 
            inQ[now] = 0;
            if(cycle[now] == v) continue;
            cycle[now]++;

            for(int i = 0; i < alen[now]; ++i){
                int next = adj[now][i];
                int d = W[now][i];

                if(dist[now] + d < dist[next]){
                    dist[next] = dist[now] + d;

                    if(inQ[next] != tc){
                        inQ[next] = tc;
                        Q.push(next);
                    }
                }
            }
        }
    }
    for(int i = 0; i <v; ++i) if(cycle[i] == v) Q.push(i); 
    while(!Q.empty()){
        int now = Q.front(); Q.pop();
        if(now == 1) return;

        for(int i = 0; i < alen[now]; ++i){
            int next = adj[now][i];
            if(cycle[next] != v){
                cycle[next]= v;
                Q.push(next);
            }
        }
    }
    return;
}

int main(){
    freopen("0Text.txt", "r", stdin);
    ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    int C;
    cin >> C;
    int tc=0;
    while(C--){
        tc++;
        queue<int> Q;
        int v, w;
        cin >> v >> w;
        for(int i = 0; i < v; ++i) {
            alen[i] = 0;
            dist[i] = 0x3f3f3f3f;
            cycle[i] = 0;
        }

        for(int i = 0; i < w; ++i){
            int a, b, d;
            cin >> a >> b >> d;
            adj[a][alen[a]] = b;
            W[a][alen[a]++] = d;
        }
        go(v);
        if(dist[1] > OVERHEAD){
            cout << "UNREACHABLE\n";
            continue;
        }
        else if(cycle[1] == v){
            cout << "INFINITY ";
        }
        else{
            cout << dist[1] << ' ';
        }

        for(int i = 0; i < v; ++i){
            dist[i] = 0x3f3f3f3f;
            cycle[i] = 0;
            for(int j = 0; j < alen[i]; ++j){
                W[i][j] = -W[i][j];
            }
        }
        go(v);
        if(cycle[1] == v){
            cout << "INFINITY\n";
        }
        else{
            cout << -dist[1] << '\n';
        }
    }
    return 0;
}