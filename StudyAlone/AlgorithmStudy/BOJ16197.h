//https://www.acmicpc.net/problem/16197
//BOJ 16197 µÎ µ¿Àü
#include<iostream>

using namespace std;

bool visit[22][22][22][22];

struct COD {
    int r1, c1;
    int r2, c2;
    COD(int r1, int  c1,int r2, int c2):r1(r1), r2(r2), c1(c1), c2(c2) {}
    COD():r1(0), r2(0),c1(0), c2(0){}
};

char map[22][22];

int m, n;
int dr[4] = {-1,1,0,0};
int dc[4] = {0,0,-1,1};

COD que[10000];

bool isout(int r, int c){
    return (r <1 || r > n || c < 1 || c > m) ;
}

int bfs(int r1, int c1, int r2, int c2){
    COD now(r1,c1,r2,c2);
    visit[r1][c1][r2][c2] = true;

    int s, e;
    s = e = 0;

    que[e++] = now;

    bool find =false;
    int turn = 0;
    
    while(s!=e){
        int cnt = e-s;
        while(cnt--){
            COD now = que[s++]; 
            if(isout(now.r1,now.c1) || isout(now.r2,now.c2)) {
                find = true;
                break;
            }

            for(int d = 0; d< 4; d++){
                COD next = now;

                next.r1 += dr[d];
                next.c1 += dc[d];

                next.r2 += dr[d];
                next.c2 += dc[d];

                if(map[next.r1][next.c1] == '#') next.r1 = now.r1, next.c1 = now.c1;
                if(map[next.r2][next.c2] == '#') next.r2 = now.r2, next.c2 = now.c2;
                
                bool out[2] = {};
                out[0] = isout(next.r1, next.c1);
                out[1] = isout(next.r2, next.c2);

                if(out[0] && out[1]) continue;
                
                if(visit[next.r1][next.c1][next.r2][next.c2]) continue;
                visit[next.r1][next.c1][next.r2][next.c2] = true;

                que[e++] = next;
            }
        }

        if(find) return turn;

        turn++;

        if(turn > 10) return -1;
    }
    return -1;
}

int BOJ16197(){
    cin >> n >> m;
    int r1=-1,r2,c1=-1,c2;
    for(int i = 1; i <= n; i++){
        for(int j =1; j <= m; j++){
            cin >> map[i][j];
            if(map[i][j] == 'o'){
                if(r1 == -1){
                    r1 = i, c1 = j;
                }
                else{
                    r2 = i, c2 = j;
                }
            }
        }
    }

    cout << bfs(r1,c1,r2,c2);
    return 0;
}