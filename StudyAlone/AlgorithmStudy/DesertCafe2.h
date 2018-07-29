#include<cstdio>
#include<cstring>
int t, n, map[22][22];
int dr[4] = {-1,1,1,-1};
int dc[4] = {1,1,-1,-1};
bool visit[101];

int max(int i1, int i2){
    return i1 > i2 ? i1 : i2;
}

int maxLen(int depth, int r, int c, const int sr, const int sc){
    if(depth == 3 && r == sr && c == sc){
        return 0;
    }
    
    if(visit[map[r][c]]) return -1;
    if(map[r][c] == -1) return -1;
    
    visit[map[r][c]] = true;

    int ret = -1;

    ret = maxLen(depth, r + dr[depth], c + dc[depth], sr, sc);

    if(depth++ < 3) ret = max(ret, maxLen(depth, r + dr[depth], c + dc[depth], sr, sc));

    visit[map[r][c]] = false;
    return ret == -1 ? -1 : ret + 1;
}

int DesertCafe2(){
    int t;
    scanf("%d\n", &t);

    for(int tc = 1; tc <= t; tc++){
        scanf("%d\n", &n);
        memset(map, -1, sizeof(map));

        for(int i = 1; i <= n; i++){
            for(int j = 1; j <= n; j++){
                scanf("%d \n", &map[i][j]);
            }
        }
        int res = -1;
        for(int i = 1; i <= n; i++){
            for(int j = 1; j <= n; j++){
                res = max(res, maxLen(0, i,j, i,j));
            }
        }
        printf("#%d %d\n", tc, res);
    }
    return 0;
}