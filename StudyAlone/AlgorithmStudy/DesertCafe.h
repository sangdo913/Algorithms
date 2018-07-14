#include<cstdio>
#include<cstring>

const int INF = -987654321;
int map[22][22];
int n;
bool ch[201];
const int dr[4] = {-1,1,1,-1};
const int dc[4] = {1,1, -1,-1};

int max(int i1, int i2){
    return i1 > i2 ? i1 : i2;
}

int getDesert(int d, const int sr, const int sc, int r, int c){
    if(d == 3 && r == sr && c == sc){
        return 0;
    }

    if(map[r][c] == 200) return INF;

    if(ch[map[r][c]]) {
        return INF;
    }
    ch[map[r][c]] = true;
    int ret = INF;
    
    ret = max(ret, getDesert(d, sr, sc, r + dr[d], c + dc[d]));

    if(d < 3)ret = max(getDesert(d + 1, sr,sc, r + dr[d + 1], c + dc[d + 1]), ret);

    ch[map[r][c]] = false;

    return ret + 1;
}

int DesertCafe(){
    int t;
    scanf("%d\n", &t);
    for(int i = 0; i < 22; i++){
        for(int j = 0; j < 22; j++) map[i][j] = 200;
    }

    for(int tc = 1; tc <= t; tc++){
        scanf("%d\n", &n);

        for(int i = 1; i <= n; i++){
            for(int j = 1; j <= n; j++){
                scanf("%d \n", &map[i][j]);
            }
        }

        int res = -1;

        for(int i = 2; i < n; i++){
            for(int j = 1; j < n; j++){
                res = max(res, getDesert(0,i,j,i,j));
            }
        }
        printf("#%d %d\n", tc, res);
    }
}