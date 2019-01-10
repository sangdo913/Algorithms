//บา!
//https://www.acmicpc.net/problem/4179
#include<iostream>
#include<queue>

using namespace std;

int dr[4] = {-1,1,0,0};
int dc[4] = {0,0,-1,1};

struct COD{
    int r,c;
};
int n,m;
char arr[1000][1001];
bool visit[10000][1000];

queue<COD> fires;
bool isout(int r, int c){return r < 0 || c < 0 || r >= n || c >= m; }

void fire(){
    COD now, next ;

    int cnt = fires.size();

    while(cnt--){
        now = fires.front(); fires.pop();

        for(int d = 0; d < 4 ; d++){
            next.r = now.r + dr[d];
            next.c = now.c + dc[d]; 

            if(isout(next.r, next.c) || arr[next.r][next.c] == 'F' || arr[next.r][next.c] =='#') continue;
            arr[next.r][next.c] = 'F';
            fires.push(next);
        }
    }
}

int bfs(int r, int c){
    COD now = {r,c}, next;
    
    queue<COD> que;
    que.push(now);
    visit[r][c] = true;

    int ret = 0;
    while(que.size()){
        fire();
        int cnt = que.size();
        while(cnt--){
            now = que.front(); que.pop();

            if(isout(now.r, now.c)) return ret;

            for(int d = 0; d < 4; d++){
                next.r = now.r + dr[d];
                next.c = now.c + dc[d];

                if(isout(next.r,next.c)){
                    que.push(next);
                    continue;
                }

                else if(visit[next.r][next.c]) continue;
                else if(arr[next.r][next.c] != '.') continue;
                visit[next.r][next.c] = true;

                que.push(next);
            }
        }
        ret++;
    }
   return -1; 
}

int Do(){
    cin >> n >> m;
    int sr, sc;
    for(int i = 0; i < n; i++) for(int j = 0; j < m; j++){
        cin >> arr[i][j];
        if(arr[i][j] == 'J') sr= i, sc = j, arr[i][j] = '.';
        else if (arr[i][j] == 'F') fires.push({i,j});
    }

    int res;
    if((res = bfs(sr,sc)) == -1){
        cout << "IMPOSSIBLE";
    }
    else cout << res;
    return 0;
}