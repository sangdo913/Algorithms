#include<iostream>
#include<queue>

using namespace std;

int line[2][101], idx = 1;
int adj[101][101];
int alen[101];

int visit[101], n, query = 1;

bool bfs(int from, int to){
    queue<int> que;
    que.push(from);

    while(que.size()){
        int now = que.front(); que.pop();
        if(now == to) return true;

        for(int i = 0; i < alen[now]; i++){
            int next = adj[now][i];

            if(visit[next] == query) continue;
            visit[next] = query;
            que.push(next);
        }
    }

    return false;
}

int Do(){
    ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    cin >> n;

    while(n--){
        int a, b,c;

        cin >> a >> b >> c;

        if(a ==1){
            line[0][idx] = b;
            line[1][idx] = c;

            for(int i  = 1; i < idx; i++){
                int x = line[0][i], y = line[1][i];

                if((b < x && x < c) || (b < y && y < c)){
                    adj[i][alen[i]++] = idx;
                }
                if((x < b && b < y) || (x < c && c < y)){
                    adj[idx][alen[idx]++] = i;
                }
            }
            idx++;
        }

        else{
            cout << bfs(b,c) << '\n';
            query++;
        }
    }
    return 0;
}