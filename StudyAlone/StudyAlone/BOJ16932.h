#include<iostream>
#include<queue>
#include<vector>

struct COD{
    int r, c;
};

using namespace std;

int n, m;
int arr[1000][1000];
int group[1000][1000];
int gcnt[1000001];
int gnum = 1;

queue<COD> que;

int dr[4] = {-1,1, 0,0};
int dc[4] = {0,0,-1,1};

bool isout(int r, int c){
    return r < 0 || c < 0 || r >= n || c >= m;
}

void makeGroup(int r, int c){
    COD now, next;
    now.r = r, now.c = c;

    que.push(now);

    while(que.size()){
        now = que.front(); que.pop();

        for(int  d= 0; d < 4; d++){
            next.r = now.r+dr[d];
            next.c = now.c  + dc[d];

            if(isout(next.r,next.c) || arr[next.r][next.c] == 0 || group[next.r][next.c]) continue;
            group[next.r][next.c] = gnum;
            gcnt[gnum]++;
            que.push(next);
        }
    }

    gnum++;
}

int Do(){
    cin >> n >> m;
    for(int i = 0; i < n; i++){
        for(int j = 0; j< m; j++){
            cin >> arr[i][j];
        }
    }

    int res = 0;
    for(int i = 0; i < n; i++){
        for(int j = 0;j < m; j++){
            if(arr[i][j] == 0 || group[i][j]) continue;
            makeGroup(i,j);
        }
    }

    for(int i = 0; i < n; i++){
        for(int j = 0;j  < m; j++){
            if(arr[i][j] == 0){
                int sum = 1; 

                for(int d = 0 ; d < 4; d++){
                    int nr = i + dr[d], nc = j + dc[d];

                    if(isout(nr,nc)) continue;
                    sum += gcnt[group[nr][nc]];
                    res = res > sum ? res : sum;
                }
            }
        }
    }
    cout << res;
    return 0;
}