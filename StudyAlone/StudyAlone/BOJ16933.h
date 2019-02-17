#include<iostream>
#include<queue>

using namespace std;

struct COD{
    int r, c, cnt, k;
};

queue<COD> que;
bool visit[1000][1000][11][2];
char arr[1000][1001];
int n, m, k, dr[5] = {0,-1,1,0,0}, dc[5] = {0,0,0,-1,1};

int Do(){
    ios_base::sync_with_stdio(false), cin.tie(0), cout.tie(0);

    cin >> n >> m>> k;

    for(int i = 0; i < n; i++) cin >> arr[i];

    que.push({0,0,1,0});
    visit[0][0][0][1] = true;

    COD next;
    while(que.size()){
        COD now = que.front(); que.pop();

        if(now.r == n-1 && now.c == m-1) return!(cout << now.cnt);

        for(int d= 0; d < 5; d++){
            next.r = now.r+dr[d], next.c = now.c+dc[d], next.cnt = now.cnt+1, next.k = now.k;

            if(next.r < 0 || next.c < 0 || next.r == n || next.c == m) continue;
            if(arr[next.r][next.c] == '1'){
                if((d == 0) || (now.k < k && now.cnt&1)){
                    if(d) next.k = now.k+1;
                    if(visit[next.r][next.c][next.k][next.cnt&1]) continue;
                    visit[next.r][next.c][next.k][next.cnt&1] = true;
                    que.push(next);
                }
                continue;
            }

            if(visit[next.r][next.c][next.k][next.cnt&1]) continue;
            visit[next.r][next.c][next.k][next.cnt&1] = true;
            que.push(next);
        }
    }
    cout << -1;
    return 0;
}