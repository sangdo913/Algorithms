#include<cstdio>
#include<cstring>

int map[1004][1004];
int dr[4] = {-2,2,0,0};
int dc[4] = {0,0,-2,2};
int n, m;
int res;

int Kong(){
    int t;
    scanf("%d\n", &t);

    for(int tc = 1; tc <= t; tc++){
        scanf("%d\n %d\n",&m, &n);
        memset(map, 0, sizeof(map));
        res = n*m;

        for(int i = 2; i <= n + 1; i++){
            for(int j = 2; j <= m + 1; j++){
                if(map[i][j]) continue;

                for(int d = 0; d < 4; d++){
                    int nr = i + dr[d];
                    int nc = j + dc[d];
                    if(nr >= 2 && nr <= n + 1 && nc >= 2 && nc <= m + 1 && map[nr][nc] == 0) {
                        map[nr][nc] = 1;
                        res--;
                    }
                }
            }
        }
        printf("#%d %d\n", tc, res);
    }
    return 0;
}