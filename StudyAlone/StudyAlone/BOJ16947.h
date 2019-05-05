#include<iostream>
#include<queue>

using namespace std;

int adj[3000][3000], n;
int alen[3000];
int chk[3000];
bool inner[3000];
queue<int> que;

int dfs(int now, int prev){
    if(chk[now] == 1){
        return now;
    }

    chk[now] = 1;
    for(int i = 0; i < alen[now]; i++){
        int next =  adj[now][i];
        if(next == prev) continue;
        int res = dfs(next,now);

        if(res == -2){chk[now] = -1; return -2;}
        else if(res == now) return -2;
        else if (res != -1){
            return res;
        }
    }
    chk[now]  = -1;

    return -1;
}

int dist[3000];

int Do(){
    ios_base::sync_with_stdio(false), cin.tie(0), cout.tie(0);

    cin >> n;

    for(int i = 0; i < n; i++){
        int a, b;
        cin >> a >> b;
        --a,--b;
        adj[a][alen[a]++] = b;
        adj[b][alen[b]++] = a;
    }

    dfs(0,-1);

    for(int i = 0; i < n; i++){
        if(chk[i] == 1){
            que.push(i);
        }
        else chk[i] = 0;
    }

    while(que.size()){
        int now = que.front(); que.pop();

        for(int i = 0; i < alen[now]; i++){
            int next = adj[now][i];
            if(chk[next]) continue;
            chk[next] = 1;
            dist[next] = dist[now] + 1;

            que.push(next);
        }
    }

    for(int  i =0; i < n; i++) cout << dist[i] << ' ';
    
    return 0;
}