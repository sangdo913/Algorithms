#include<iostream>
#include<cstring>
#include<queue>
#include<cstdio>

using namespace std;

int s[10], n, m, p;
char arr[1000][1000];
int dr[4] = {-1,1,0,0};
int dc[4] = {0,0,-1,1};
int sz[10];

bool isout(int r, int c){
    return r < 0 || c < 0 || r>= n || c >=m;
}
struct COD{
    int r,c, cnt;
};

bool operator<(const COD& c1, const COD c2){
    return c1.cnt < c2.cnt;
}

queue<COD> que[10];

bool visit[1000][1000] = {};

int Do(){
    cin >> n >> m >> p;

    int res[10] = {};

    memset(visit, false, sizeof(visit));

    for(int i = 1; i <= p; i++) {
        cin >> s[i];
    }

    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++) {
            cin >> arr[i][j];
            if('1' <= arr[i][j] && arr[i][j] <= '9'){
                que[arr[i][j]-'0'].push({i,j,0});
            }
        }
    }

    bool end = false;

    while(!end){
        end = true;

        for(int i = 1; i <= p; i++){
            for(int k = 0; k < s[i]; k++){
                int cnt = que[i].size();
                if(cnt == 0) break;

                while(cnt--){
                    COD now = que[i].front(); que[i].pop();
                    now.cnt = k == 0 ? s[i] : now.cnt;

                    COD next;
                    
                    for(int d= 0; d < 4; d++){
                        next.r = now.r + dr[d];
                        next.c = now.c + dc[d];
                        next.cnt = now.cnt-1;
                        
                        if(now.cnt == 0) {
                            continue;
                        }

                        if(isout(next.r,next.c) || visit[next.r][next.c] || ( arr[next.r][next.c] != '0'+i && arr[next.r][next.c] !='.'))
                        continue;

                        arr[next.r][next.c] = '0'+i;
                        end = false;

                        visit[next.r][next.c] = true;
                        que[i].push(next);
                    }
                }
            }

        }
    }

    for(int i = 0; i < n; i++) for(int j = 0; j < m; j++){
        if('1'<= arr[i][j] && arr[i][j] <='9'){
            res[arr[i][j] -'0'] ++;
        }
    }

    for(int i = 1; i <= p ; i++) cout << res[i] << ' ';
    return 0;
}
