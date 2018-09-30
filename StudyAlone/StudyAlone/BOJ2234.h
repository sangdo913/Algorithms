#include<iostream>

using namespace std;

enum dir {W= 1, N = 2, E= 4, S = 8};

int map[50][50];
int dr[4] = {-1,1,0,0};
int dc[4] = {0,0,-1,1};
int n, m;

int conv[4] = {N, S, W, E};

int visit[50][50];
int rnum = 1;

int rs[500];

int MAX(int i1, int i2){return i1 > i2 ? i1 : i2;}

int bfs(int r, int c){
    int que[300][2], fr, re;
    fr = re= 0;

    que[re][0] = r;
    que[re++][1] = c;
    
    visit[r][c] = rnum;
    int res = 0;

    while(fr!=re){
        int now[2] = {que[fr][0], que[fr++][1]};
        res++;

        for(int d = 0; d < 4; d++){
            if(conv[d] & map[now[0]][now[1]]) continue;
            
            int next[2] = {now[0] + dr[d], now[1] + dc[d]};

            if(visit[next[0]][next[1]]) continue;
            visit[next[0]][next[1]] = rnum;

            que[re][0] = next[0];
            que[re++][1] = next[1];
        }
    }
    return res;
}

int BOJ2234(){
    cin >> n >> m;

    for(int i = 0; i < m; i++){
        for(int j = 0; j < n ; j++){
            cin >> map[i][j];
        }
    }

    int res[3] = {};

    for(int i = 0; i < m; i++){
        for(int j = 0; j < n ; j++){
            if(visit[i][j]) continue;
            
            res[0]++;
            rs[rnum] = bfs(i,j);
            res[1] = MAX(res[1], rs[rnum]);
            rnum++;
        }
    }

    for(int i =0; i < m; i++){
        for(int j =0; j < n;j ++){
            for(int d = 0; d < 4; d++){
                if(map[i][j] & conv[d]){
                    int next[2] = {i+dr[d], j + dc[d]};
                    if(next[0] < 0 || next[1] < 0 || next[0] > n-1 ||next[1] > m-1 ) continue;
                    int r1 = visit[i][j];
                    int r2 = visit[next[0]][next[1]];
                    
                    if(r1 == r2) continue;

                    if(rs[visit[i][j] == rs[visit[next[0]][next[1]]]]) continue;

                    res[2] = MAX(res[2], rs[visit[i][j]] + rs[visit[next[0]][next[1]]]);
                }
            }
        }
    }

    cout << res[0] << '\n' << res[1] << '\n' << res[2] << '\n';

    return 0;
}