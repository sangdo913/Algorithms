#include<cstdio>
#include<cstring>

int map[10][10], n, m;
int que[1000][2], f, r;

int dr[8] = {0,-1,-1,-1,0,1,1,1};
int dc[8] = {-1,-1,0,1,1,1,0,-1};

int numsOfChange(int ro, int c, int turn){

    int res = 0;
    for(int d = 0; d < 8; d++){
        f = r = 0;
        int tr = ro + dr[d], tc = c + dc[d];

        while(map[tr][tc] && map[tr][tc] != -1 && map[tr][tc] != turn){
            que[r][0] = tr;
            que[r++][1] = tc;

            tr += dr[d];
            tc += dc[d];
        }

        if(map[tr][tc] == turn){
            res += r - f;

            while(f != r){
                map[que[f][0]][que[f][1]] = turn;
                f++;
            }
        }
    }

    return res;
}


int FunnyOcello()
{
    int t;
    scanf("%d\n", &t);

    for(int tc = 1; tc <= t; tc++){
        scanf("%d %d\n", &n, &m);

        memset(map, -1, sizeof(map));
        for(int i = 1; i <= n; i++){
            for(int j =1; j <= n; j++){
                map[i][j] = 0;
            }
        }

        map[n/2][n/2] = 2;
        map[n/2 + 1][n/2] = 1;
        map[n/2+1][n/2+1] = 2;
        map[n/2][n/2+1] =1;
        int nums[3] = {0,2,2};
        while(m--){
            int r, c, turn;
            scanf("%d %d %d\n", &c, &r, &turn);
            nums[turn]++;
            map[r][c] = turn;
            int change = numsOfChange(r,c,turn);
            nums[turn] += change;
            nums[turn^3] -= change;
        }

        printf("#%d %d %d\n", tc, nums[1], nums[2]);
    }
    return 0;
}