#include<iostream>
#include<cstring>

using namespace std;

char map[32][32];

int n, m;
int dr[4] = {-1,1,0,0};
int dc[4] = {0,0,-1,1};
int res = 0x3f3f3f3f;
int dst;
int MIN(int i1, int i2){return i1 < i2 ? i1 : i2;}
bool check[32][32];
bool visit[4][32][32];

void dfs(int r, int c, int num, int cnt){
    if(cnt == dst ){
        res = MIN(num , res);
        return; 
    }
    if(cnt == res) return;

    bool tv[32][32];
    bool tv2[4][32][32];
    memcpy(tv, check, sizeof(tv));
    memcpy(tv2, visit, sizeof(tv2));

    for(int d = 0; d < 4; d++){
        if(visit[d][r][c]) continue;
        visit[d][r][c] = true;

        int ncnt = cnt;
        int now[2] = {r, c};
        int next[2] = {r + dr[d], c + dc[d]};
        while(map[next[0]][next[1]] == '.'){
            if(!check[now[0]][now[1]]){
                visit[d][now[0]][now[1]] = true;
                ncnt++;
                check[now[0]][now[1]] =true;
            }

            now[0] = next[0];
            now[1] = next[1];
            next[0] += dr[d];
            next[1] += dc[d];
        }
        
        
        visit[d][now[0]][now[1]] = true;
        if(!check[now[0]][now[1]]){
            ncnt++;
            check[now[0]][now[1]] = true;
        }

        if(now[0] == r && now[1] == c){
            visit[d][r][c] = false;
            memcpy(check,tv,sizeof(tv));
            memcpy(visit,tv2, sizeof(tv2));
            continue;
        } 

        if(ncnt == dst){
            res = MIN(res, num);
            memcpy(check,tv,sizeof(tv));
            memcpy(visit,tv2, sizeof(tv2));
            visit[d][r][c] = false;;
            return; 
        }
        dfs(now[0], now[1], num+1, ncnt);
        memcpy(check,tv,sizeof(tv));
        memcpy(visit,tv2, sizeof(tv2));
        visit[d][r][c] = false;
    }
    
}

int BOJ9944(){
    int t = 1;
    while(cin >> n >> m){
        res = 0x3f3f3f3f;
        memset(map, '*', sizeof(map));
        dst = 0;
        for(int i = 1; i <= n; i++){
            for(int j = 1; j <= m; j++){
                cin >> map[i][j];
                if(map[i][j] == '.') dst++;
            }
        }

        

        for(int i = 1; i <= n; i++){
            for(int j =1; j <= m; j++){
                if(map[i][j] == '.')
                {
                    dfs(i,j,0,0);
                }
            }
        }
        cout <<"Case " << t++ << ": "<< res << '\n';
    }
    return 0;
}