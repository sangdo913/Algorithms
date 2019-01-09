//«Á?«º
//https://www.acmicpc.net/problem/5558

#include<iostream>
#include<queue>

using namespace std;

int n, h,w;
char arr[1000][1001];

int dr[4] = {-1,1,0,0};
int dc[4] = {0,0,-1,1};

bool isout(int r, int c){return r < 0 || c < 0 || r >= h || c >= w;}
bool isdigit(int r, int c){return arr[r][c] >= '0' && arr[r][c] <= '9'; }

struct COD{
    int r, c, l, visit;
};

bool visit[1000][1000][10];

int bfs(int r, int c){
    COD now = {r,c,1}, next;

    queue<COD> que;
    que.push(now);
    visit[r][c][1] = true;

    int ret = 0;
    while(que.size()){
        int cnt = que.size();
        while(cnt--){
            now = que.front(); que.pop();
            if(now.l == n+1) return ret-1;

            for(int d = 0; d < 4; d++){
                next.r = now.r + dr[d];
                next.c = now.c + dc[d];
                next.l = now.l;
                next.visit = now.visit;

                if(isout(next.r,next.c)) continue;
                if(arr[next.r][next.c] == 'X') continue;

                if(isdigit(arr[now.r][now.c])){
                    int cnum = arr[now.r][now.c] - '0';

                    if(((((now.visit) & (1<<cnum)) == 0)) && (cnum <= now.l)){
                        next.visit |= (1 << cnum);
                        next.l++;
                    }
                }

                if(visit[next.r][next.c][next.l]) continue;
                visit[next.r][next.c][next.l] = true;
                que.push(next);
            }
        }
        ret++;
    }
    return -1;
}
int Do(){
    cin >> h >> w >> n;

    int sr, sc;
    for(int i = 0; i < h; i++){
        cin >> arr[i];
        for(int j = 0; j < w; j++){
            if(arr[i][j] == 'S') sr= i, sc = j;
        }
    }

    cout << bfs(sr,sc);
    return 0;
}