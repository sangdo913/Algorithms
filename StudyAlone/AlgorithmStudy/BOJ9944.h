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

void dfs(int r, int c, int num, int &cnt){
    if(cnt == dst ){
        res = MIN(num , res);
        return; 
    }
    if(num == res) return;

    int restore[2] = {r,c};

    for(int d = 0; d < 4; d++){
        int now[2] = {r, c};
        int next[2] = {r + dr[d], c + dc[d]};

        while(map[next[0]][next[1]] == '.'){
            if(map[now[0]][now[1]] == '.'){
                cnt++;
                map[now[0]][now[1]] ='*';
            }

            now[0] = next[0];
            now[1] = next[1];
            next[0] += dr[d];
            next[1] += dc[d];
        }
        
        
        if(map[now[0]][now[1]] == '.'){
            cnt++;
            map[now[0]][now[1]] = '*';
        }

        if(!(now[0] == r && now[1] == c)){
            dfs(now[0], now[1], num+1, cnt);
        } 

        while(now[0] != restore[0] || now[1] != restore[1]){
            if(map[now[0]][now[1]] == '*'){
                map[now[0]][now[1]] = '.';
                cnt--;
            }

            now[0] -= dr[d];
            now[1] -= dc[d];
        }

        if(map[now[0]][now[1]] == '*'){
            map[now[0]][now[1]] = '.';
            cnt--;
        }
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
                    map[i][j] = '*';
                    int cnt = 1;
                    dfs(i,j,0,cnt);
                }
            }
        }
        cout <<"Case " << t++ << ": "<< (res == 0x3f3f3f3f ? -1 : res) << '\n';
    }
    return 0;
}