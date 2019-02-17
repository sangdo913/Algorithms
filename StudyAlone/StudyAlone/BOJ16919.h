#include<iostream>
#include<queue>

struct ST{
    int r, c, time;
};

using namespace std;
char res[6][200][200];
char init[200][200];
int r,c,n;
int dr[4] = {-1,1,0,0};
int dc[4] = {0,0,-1,1};

bool isout(int nr, int nc){
    return nr < 0 || nc < 0 || nr >= r || nc >= c;
}

int Do(){
    queue<ST> que;
    cin >> r >> c >> n;

    for(int i = 0; i < r; i++){
        for(int j = 0; j<c;j++){
           cin >> res[0][i][j];
           init[i][j] = res[0][i][j]; 
           if(res[0][i][j] == 'O') 
                que.push({i,j,3});
            }
    }

    for(int ti = 0; ti < 6; ti++){
        if(ti > 1){
            for(int i = 0; i < r; i++) for(int j = 0; j < c; j++) if(init[i][j] =='.') que.push({i,j,3}), init[i][j] = 'O';
        }

        int cnt = que.size();

        while(cnt--){
            ST now = que.front(); que.pop();

            if(now.time){
                now.time--;
                if(init[now.r][now.c] == 'O') que.push(now);
            }

            else{
                init[now.r][now.c] = '.';

                for(int d =0 ; d < 4; d++){
                    int nr = now.r + dr[d], nc = now.c + dc[d];
                    if(isout(nr,nc)) continue;
                    
                    init[nr][nc] = '.';
                }
            }
        }

        if(ti){
            for(int i = 0; i < r; i++) for(int j = 0;j < c; j++) res[ti][i][j] = init[i][j];
        }
    }

    int rnum;
    if(n== 1) rnum = 0;
    else if (n&1){
        if((n/2) & 1){
            rnum = 3;
        }
        else rnum = 5;
    }
    else{
        rnum = 2;
    }

    for(int i = 0; i < r; i++) {
        for(int j = 0; j < c; j++) cout <<res[rnum][i][j];
        cout << '\n';
    }
    return 0;
}