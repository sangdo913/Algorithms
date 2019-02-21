#include<iostream>
#include<queue>

using namespace std;

int dr[3][8] = {
    {-1,1,0,0},{-1,-1,1,1},{-1,-2,-2,-1,1,2,2,1}
};
int dc[3][8] = {
    {0,0,-1,1}, {-1,1,-1,1},{-2,-1,1,2,-2,-1,1,2} };
int dlen[3] = {4, 4, 8};

struct COD{
    int r,c,num, mal;
};

int n;
int arr[10][10];

queue<COD> que;

bool inque[3][10][10][102];

int Do(){
    cin >> n;
    COD now, next;
    for(int i = 0; i < n; i++) for(int j = 0; j < n; j++) {
        cin >> arr[i][j];
        if(arr[i][j] == 1) now.r = i , now.c =j;
    }
    
    now.num = 2;
    for(int i  =0; i < 3; i++) now.mal = i, que.push(now), inque[now.mal][now.r][now.c][now.num] = true;

    int time = 0;

    while(que.size()){
        int cnt = que.size();

        while(cnt--){
            now = que.front(); que.pop();
            if(now.num == n*n+1) return!(cout << time); 

            for(int d = 0; d < dlen[now.mal]; d++){
                next = now;
                next.r += dr[now.mal][d], next.c += dc[now.mal][d];

                while(0<=next.r && next.r < n && 0<=next.c && next.c < n){
                    next.num = now.num + (arr[next.r][next.c] == now.num);

                    if(!inque[next.mal][next.r][next.c][next.num]){
                        inque[next.mal][next.r][next.c][next.num] = true;
                        que.push(next);
                    } 

                    next.r += dr[now.mal][d], next.c += dc[now.mal][d];

                    if(now.mal == 2) break;
                }
            }

            for(int mal = 0; mal < 3; mal++){
                if(now.mal == mal) continue;
                next = now;
                next.mal = mal;
                if(inque[next.mal][next.r][next.c][next.num]) continue;
                inque[next.mal][next.r][next.c][next.num] = true;
                que.push(next);
            }
        }

        time++;
    }
    cout << "wrong";
    return 0;
}