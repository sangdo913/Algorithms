#include<iostream>
#include<cstring>
#include<queue>

using namespace std;

int arr[200][200], r,c,n;
char res[200][200];
int dr[4] = {-1,1,0,0};
int dc[4] = {0,0,-1,1};

struct st{
    int r,c,time;
};

bool isout(int rr, int cc){
    return rr < 0 || rr >= r || cc < 0 || cc >= c; 
}

int Do(){
    cin >> r >> c >> n;

    memset(res, 'O', sizeof(res));

    queue<st> que;

    char in;
    for(int i = 0; i < r; i++){
        for(int j = 0; j < c; j++){
            cin >> res[i][j];
            if(res[i][j] == 'O'){
                que.push({i,j,3});
            }
        } 
    }

    int ti = 0;

    while(ti != n+1){
        if(ti > 1)
            for(int i = 0; i < r; i++){
                for(int j = 0; j < c ; j++) if(res[i][j] == '.') res[i][j] = 'O', que.push({i,j,3});
            }

        int cnt = que.size();

            while(cnt--){
                st now = que.front(); que.pop();

                if(now.time == 0){
                    res[now.r][now.c] = '.';

                    for(int d =0; d < 4; d++){
                        int nr = now.r + dr[d];
                        int nc = now.c + dc[d];
                        if(isout(nr,nc)) continue;

                        res[nr][nc] = '.';
                    }
                    
                }
                else{
                    --now.time;
                    
                    if(res[now.r][now.c] == 'O') que.push(now);
                }
            }

        ti++;
    }

    for(int i = 0; i < r; i++){
        for(int j = 0; j < c; j++) cout << res[i][j];
        cout <<'\n';
    }
    return 0;
}