#include<cstdio>
#include<cstring>

enum DIR {UP = 0b1000, DOWN = 0b0100, LEFT = 0b0010, RIGHT = 0b0001};

const int dr[4] = {-1,1,0,0};
const int dc[4] = {0,0,-1,1};
const int ch[8] = {0, UP|DOWN | LEFT|RIGHT, UP|DOWN, LEFT|RIGHT, UP|RIGHT, RIGHT |DOWN, LEFT | DOWN, LEFT | UP};
const int d2[2][4] = {{UP, DOWN, LEFT,RIGHT}, {DOWN, UP, RIGHT, LEFT}};
int map[52][52], que[500][2], fr, re, visit[52][52] = {0};

int numOfPlace(int r, int c, int l, int t){
    fr = re = 0;
    int ret = 0;
    que[re][0] = r;
    que[re++][1] = c;
    visit[r][c] = t;
    
    int cnt = 1;

    while(fr != re){
        int nr = que[fr][0];
        int nc = que[fr++][1];
        ret++;
        cnt--;

        for(int d = 0; d < 4; d++){
            int nnr = nr + dr[d];
            int nnc = nc + dc[d];
            int type[2] = {ch[map[nr][nc]], ch[map[nnr][nnc]]};

            if(map[nnr][nnc] == -1) continue;
            if(visit[nnr][nnc] == t) continue;
            
            if((type[0] & d2[0][d]) && (type[1] & d2[1][d])){
                que[re][0] = nnr;
                que[re++][1] = nnc;
                visit[nnr][nnc] = t;
            } 
        }

        if(cnt == 0) {
            cnt = re - fr;
            l--;
            if(l == 0) return ret;
        }
    }
    return ret;
}


int TalJuBeom(){
    int n, m, t, r, c, l ;
    scanf("%d\n", &t);

    for(int tc = 1; tc <= t; tc++){
        scanf("%d %d %d %d %d\n", &n, &m, &r, &c, &l);
        r++; c++;
        
        memset(map, -1, sizeof(map));

        for(int r = 1; r <= n; r++){
            for(int c = 1; c <= m; c++){
                scanf("%d \n", &map[r][c]);
            }
        }

        int res = numOfPlace(r, c, l, tc);

        printf("#%d %d\n", tc, res);
    }


    return 0;
}