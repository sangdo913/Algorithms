#include<cstdio>

int map[10][10],n, m,  c;

int getMaxHoney(int x1, int y1, int x2, int y2){
    int maxes[2] = {0,0}, cmp[2] = {0,0}, val[2] = {0,0};
    for(int bit = 1; bit < (1 << m); bit++){
        int idx = 0;
        int tb = bit;
        cmp[0] = 0;
        cmp[1] = 0;
        val[0] = 0;
        val[1] = 0;
        while(tb){
            if(tb & 1){
                cmp[0] += map[y1][x1 + idx];
                cmp[1] += map[y2][x2 + idx];
                val[0] += map[y1][x1 + idx] * map[y1][x1 + idx];
                val[1] += map[y2][x2 + idx] * map[y2][x2 + idx];
            }
            idx++;
            tb >>= 1;
        }
        if(cmp[0] <= c){
            maxes[0] = val[0] > maxes[0] ? val[0] : maxes[0];
        }
        if(cmp[1] <= c){
            maxes[1] = val[1] > maxes[1] ? val[1] : maxes[1];
        }
    }
    return maxes[0] + maxes[1];
}


int getHoney(){
    int t;
    scanf("%d\n", &t);
    int ret = 0;
    for(int tc = 1; tc <= t; tc++){
        scanf("%d %d %d\n", &n, &m, &c);
        ret = 0;
        for(int i = 0; i < n; i++){
            for(int j = 0; j < n; j++) scanf("%d \n", &map[i][j]);
        }
        for(int i = 0; i < n; i++){
            for(int j = 0; j + m <= n; j++){
                for(int i2 = i; i2 < n; i2++){
                    int j2 = i2 == i ? j + m : 0;
                    for(; j2 + m <= n; j2++){
                        int temp = getMaxHoney(j,i,j2,i2);
                        ret = ret > temp ? ret : temp;
                    }
                }
            }
        }
        printf("#%d %d\n", tc, ret);
    }
}