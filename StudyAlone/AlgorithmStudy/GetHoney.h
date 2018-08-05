#include<cstdio>

int map[10][10];
int n,m,c, max;

int price(int x, int y, int visit){
    int idx = 0, ret = 0, cmp = 0;
    
    while(visit){
        if(visit & 1){
            cmp += map[y][x+idx];
            ret += map[y][x+idx]*map[y][x+idx];
        }
        
        idx++;
        visit >>= 1;
    }

    return cmp <= c ? ret : 0;
}

int MAX(int i1, int i2){
    return i1 > i2 ? i1 : i2;
}

int getMax(int p1x, int p1y, int p2x, int p2y){
    int bit = 1;
    int p1 = 0, p2 = 0;
    for(int bit = 1; bit < (1 << m); bit++){
        int tp = price(p1x,p1y, bit);
        int tp2 = price(p2x, p2y, bit);
        p1 = MAX(p1, tp);
        p2 = MAX(p2, tp2);
    }
    return p1 + p2;
}

int GetHoney(){
    int t;
    scanf("%d\n", &t);

    for(int tc = 1; tc <= t; tc++){
        scanf("%d %d %d\n", &n, &m, &c);
        for(int i = 0; i < n; i++){
            for(int j = 0 ; j < n ; j++){
                scanf("%d \n", &map[i][j]);
            }
        }

        int res = 0;
        for(int i = 0 ; i < n; i++){
            for(int j = 0; j + m <= n; j++){
                for(int i2 = i; i2 < n; i2++){
                    int j2 = i2 == i ? j + m : 0;
                    for(; j2 + m <= n; j2++){
                        res = MAX(res, getMax(j,i,j2,i2)); 
                    }
                }
            }
        }
        printf("#%d %d\n", tc, res);
    }

    return 0;
}