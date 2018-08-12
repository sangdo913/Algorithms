#include<cstdio>
#include<cstring>

int fr, re, que[400][2];
int max, n,m, map[22][22], houses;
bool visit[22][22];
int cost[42];
int dr[4] = {-1,1,0,0};
int dc[4] = {0,0,-1,1};

int maxHouse(int r, int c){
    int cnt = 0;
    int ret = 0;
    int co = 1;
    
    visit[r][c] = true;
    fr = re = 0;
    que[re][0] = r;
    que[re++][1] = c;
    
    int sz = 1;
    while(houses != cnt){
        while(sz){
            int cod[2] = {que[fr][0], que[fr][1]};
            fr++;
            cnt += map[cod[0]][cod[1]];

            for(int d = 0; d < 4; d++){
                int nr = cod[0] + dr[d];
                int nc = cod[1] + dc[d];
                if(map[nr][nc] == -1) continue;
                if(visit[nr][nc]) continue;

                visit[nr][nc] = true;
                que[re][0] = nr;
                que[re++][1] = nc;
            }
            sz--;
        }

        ret = cost[co] <= cnt * m ? cnt : ret;
        sz = re - fr;
        co++;
    }
    return ret;
}

int MAX(int i1, int i2){
    return i1 < i2 ? i2 : i1;
}
int homeBang(){
    for(int i = 1; i < 42; i++){
        cost[i] = i*i + (i-1)*(i-1);
    }

    int t;
    scanf("%d\n", &t);

    for(int tc = 1; tc <= t; tc++){
        memset(map, -1, sizeof(map));
        scanf("%d %d\n", &n, &m);
        houses = 0;
        for(int i = 1; i <= n; i++){
            for(int j = 1; j <= n; j++){
                scanf("%d \n", &map[i][j]);
                houses += map[i][j];
            }
        }

        int res  = 0;

        for(int i = 1; i <= n; i++){
            for(int j = 1; j <= n; j++){
                memset(visit,false, sizeof(visit));
                res = MAX(res, maxHouse(i,j));
            }
        }
        printf("#%d %d\n", tc, res);
    }
    return 0;
}