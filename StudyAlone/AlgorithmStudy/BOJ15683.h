//https://www.acmicpc.net/problem/15683
//BOJ15683 °¨½Ã
#include<iostream>

using namespace std;

int dr[4] = {-1,0,1,0};
int dc[4] = {0, 1, 0,-1};

int csize[6] = {0,4,2,4, 4,1};
int camera[6][4] = {{}, {0}, {1,3}, {0, 1}, {0,1,3}, {0,1,2,3}};
int dcnt[6] = {0,1,2,2,3,4};

int map[8][8], n, m;
int MIN(int i1, int i2){return i1 < i2 ? i1 : i2;}
int getNum(){
    int res = 0;
    for(int i = 0 ; i < n; i++){
        for(int j = 0; j < m; j++){
            res += map[i][j] == 0;
        }
    }
    return res;
}

int dfs(int r, int c){
    if(r == n){
        return getNum();
    }

    int next[2] = {r, c+1};
    if(next[1] == m){
        next[0] ++;
        next[1] = 0;
    }
    int res = 0x3f3f3f3f;

    if(map[r][c] > 0 && map[r][c] != 6){
        int ca = map[r][c];

        for(int rot = 0; rot < csize[ca]; rot++){
            
            for(int d= 0; d < dcnt[ca]; d++){
                int p[2] = {r,c};
                while(p[0] < n && p[1]< m && p[0] >= 0 && p[1] >= 0){
                    if(map[p[0]][p[1]] == 6) break;

                    if(map[p[0]][p[1]] <= 0){
                        map[p[0]][p[1]]--;
                    }
                    int dir = (rot+camera[ca][d])%4;
                    p[0]+= dr[dir];
                    p[1]+= dc[dir];
                }
            }
            
            res = MIN(res, dfs(next[0],next[1]));

            for(int d = 0; d < dcnt[ca]; d++){
                int p[2] = {r,c};
                while(p[0] >= 0 && p[1] >= 0 && p[0] < n && p[1] < m){
                    if(map[p[0]][p[1]] == 6) break;
                    if(map[p[0]][p[1]] < 0 ){
                        map[p[0]][p[1]]++;
                    }
                    int dir = (rot+camera[ca][d])%4;
                    p[0]+= dr[dir];
                    p[1] += dc[dir];
                }
            }
        }
    } 
    else{
        res = dfs(next[0], next[1]);
    }

    return res;
}

int BOJ15683(){
    cin >> n >> m;
    for(int i = 0 ; i < n; i++){
        for( int j = 0; j < m; j++){
            cin >> map[i][j];
        }
    }
    cout << dfs(0,0);

    return 0;
}