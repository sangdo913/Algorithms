#include<iostream>
#include<queue>

using namespace std;

char arr[8][9];

int dr[9] = {0,-1,1, 0,0, 1,1,-1,-1};
int dc[9] = {0, 0,0,-1,1,-1,1,-1, 1};
struct COD{int r; int c;};

queue<COD> que;
bool inque[8][8];

int Do(){
    for(int i = 0; i < 8; i++) cin >> arr[i];

    que.push({7,0});
    COD now, next;
    inque[7][0] = true;

    for(int  i = 0 ; i < 8; i++){
        int cnt = que.size();
        while(cnt--){
            now = que.front(); que.pop();
            inque[now.r][now.c] =  false;
            if(arr[now.r][now.c] == '#') continue;

            for(int d = 0; d < 9; d++){
                next.r = now.r + dr[d], next.c = now.c + dc[d];

                if(next.r < 0 || next.c < 0 || next.r >= 8 || next.c >= 8) continue;
                if(arr[next.r][next.c] == '#') continue;
                if(inque[next.r][next.c]) continue;
                inque[next.r][next.c] = true;

                que.push(next);
            } 
        }
        for(int i = 7; i > 0; --i){
            for(int j = 0; j < 8; j++){
                arr[i][j] = arr[i-1][j];
            }
        }

        for(int j = 0;j < 8; j++) arr[0][j] = '.';
    }

    cout << !que.empty();
    return 0;
}