#include<iostream>
#include<queue>

using namespace std;

struct COD{
 int r, c,mal, num, change;
};

queue<COD> que;

int dr[3][8] = {
    {-1,1,0,0}, {-1,-1,1,1}, {-1,-2,-2,-1,1,2,2,1}
};

int dc[3][8] ={
    {0,0,-1,1}, {1,-1,1,-1}, {-2,-1,1,2,-2,-1,1,2}
};
int dlen[3] = {4,4,8};

int visit[3][10][10][102], n, arr[100][100];

int Do(){
    COD now,next;
    cin >> n;
    for(int i = 0; i < n; i++) for(int j = 0; j < n; j++) {
        cin >> arr[i][j];
        if(arr[i][j] == 1) now.r = i, now.c = j;
    }

    memset(visit, 0x3f, sizeof(visit));
    now.num = 2, now.change = 0;
    for(int i = 0; i < 3; i++) now.mal = i, que.push(now), visit[now.mal][now.r][now.c][now.num] = 0;

    int time = 0;
    bool end = false;
    int res = 0x3f3f3f3f;
    while(que.size()){
        int cnt = que.size();
        while(cnt--){
            now = que.front(); que.pop();
            if(now.num == n*n+1) {
                end = true;
                res = now.change < res ? now.change : res;
                continue;
            }

            for(int d = 0; d < dlen[now.mal]; d++){
                next = now;
                next.r += dr[now.mal][d], next.c += dc[now.mal][d];
                
                while(0 <= next.r && next.r < n && 0<=next.c && next.c < n){
                    next.num = now.num + (arr[next.r][next.c] == now.num);
                    if(visit[next.mal][next.r][next.c][next.num] > now.change){
                        visit[next.mal][next.r][next.c][next.num] = now.change;
                        que.push(next);
                    }

                    if(now.mal == 2) break;
                    next.r += dr[now.mal][d], next.c += dc[now.mal][d];
                }
            }

            for(int i = 0; i < 3; i++){
                next = now;
                next.mal = i;
                next.change += i != now.mal;

                if(visit[next.mal][next.r][next.c][next.num] > next.change){
                    visit[next.mal][next.r][next.c][next.num] = next.change;
                    que.push(next);
                }
            }
        }
        if(end)  break;
        time++;
    }

    cout << time << ' ' << res; 
    return 0;
}