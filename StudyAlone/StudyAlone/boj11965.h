//Bessie's Dream
//https://www.acmicpc.net/problem/11965
#include<iostream>
#include<queue>

using namespace std;

int arr[1000][1000];
bool visit[1000][1000][4][2];
int dr[4] = {-1,1,0,0};
int dc[4] = {0,0,-1,1}, n,m;

bool canmove(int r, int c, bool smell)
{
    if(r< 0 || c < 0 || r >= n || c >= m) return false;

    switch(arr[r][c]){
        case 0: return false;
        case 3: return smell;
        default: return true;
    }
    return true;
}

struct COD{
    int r, c, d;
    bool smell;
};


int bfs(){
    COD now = {0,0,0},next;

    queue<COD> que;
    que.push(now);

    visit[now.r][now.c][now.d][now.smell] = true;

    int ret = 0;
    while(que.size()){
        int cnt = que.size();

        while(cnt--){
            now = que.front(); que.pop();
            next = now;
            
            if(now.r == n-1 && now.c == m-1) return ret; 
            if(arr[now.r][now.c] == 4){
                next.r += dr[now.d];
                next.c += dc[now.d];
                next.smell = false;

                if(canmove(next.r,next.c, false)){
                    que.push(next);
                    continue;
                }
            }

            for(int d= 0 ; d < 4 ;d++){
                next = now;
                next.r += dr[d];
                next.c += dc[d];
                next.d = d; 
                next.smell |= arr[next.r][next.c] == 2;
                next.smell &= !(arr[next.r][next.c] == 4);

                if(canmove(next.r,next.c, next.smell)){
                    if(visit[next.r][next.c][next.d][next.smell]){ continue; }
                    visit[next.r][next.c][next.d][next.smell] = true;

                    que.push(next);
                }
            }
        }
        ret++;
    }

    return -1;
}

int Do(){
    cin >> n >> m;
    for(int i = 0; i < n; i++) for(int j = 0; j < m; j++) cin >> arr[i][j];

    cout << bfs();
    return 0;
}