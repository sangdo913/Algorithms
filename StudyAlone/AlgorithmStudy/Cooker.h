#include<cstdio>

int sinerge[16][16],n;
int res;
int abs(int i){return i >0 ? i : -i;}
int min(int i1, int i2){return i1 < i2 ? i1 : i2;}
bool check[16];

int getSi(int bit){
    int sv[2] = {0,0};
    for(int i = 0; i < n; i++){
        for(int j = i + 1; j < n; j++){
            if(bit & (1<<i) && bit & (1<<j)){
                sv[1] += sinerge[i][j];
                sv[1] += sinerge[j][i];
            }
            else if((bit & (1<<i)) == 0 && (bit & (1 << j)) == 0){
                sv[0] += sinerge[i][j];
                sv[0] += sinerge[j][i];
            }
        }
    }
    return abs(sv[0] - sv[1]);
}
int getZero(int i){
    int res = 0;
    while((i&1) == 0){
        res++;
        i>>=1;
    }
    return res;
}
int Cooker(){
    int t;
    scanf("%d \n", &t);

    for(int tc= 1; tc <= t; tc++){
        scanf("%d\n", &n);
        res = 0x7fffffff;
        for(int i = 0; i < n; i++){
            for(int j = 0; j < n; j++){
                scanf("%d \n", &sinerge[i][j]);
            }
        }
        int bit = (1 << (n/2)) - 1;
        while(bit < (1 << n)){
            int temp = bit | ((bit& -bit)-1);
            res = min(res, getSi(bit));
            bit = (temp + 1) | (((~temp & -~temp)-1) >>(getZero(bit) + 1));
        }
        printf("#%d %d\n", tc, res);
    }
    return 0;
}