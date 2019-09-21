#include<iostream>

using namespace std;

int clocks[16],temp[16];
int ch[4][4];
int sw[10][5] = {{0,1,2},{3,7,9,11},{4,10,14,15},{0,4,5,6,7},{6,7,8,10,12},{0,2,14,15},{3,14,15},{4,5,7,14,15},{1,2,3,4,5},{3,4,5,9,13}};
int slen[10] = {3,4,4,5,5,4,3,5,5,5};

int res ;
bool check(){
    for(int i = 0; i < 16; ++i) if(temp[i] %4) return false;
    return true;
}

int gogo(int bit){
    int cnt =0;
    int ret = 0;

    for(int i = 0; i < 16; ++i) temp[i] = clocks[i];
    int idx = 0;

    while(bit){
        cnt = bit % 4;
        for(int j = 0; j < slen[idx]; ++j){
            temp[sw[idx][j]] += cnt;
        }
        ret += cnt;
        if(ret >= res) return 0x3f3f3f3f;
        bit>>=2;
        idx++;
    }

    return check() ? ret : 0x3f3f3f3f;
}

int main(){
    freopen("0Text.txt", "r", stdin);
    int c;
    
    scanf("%d\n", &c);
    while(c--){
        res = 0x3f3f3f3f;
        int temp;
        for(int i = 0; i < 16 ;++i)  scanf("%d", clocks + i), clocks[i]/=3;

        for(int i = 0; i < (1<<20); ++i){
            temp = gogo(i);
            res = temp < res ? temp : res;
        }
        printf("%d\n", res == 0x3f3f3f3f? -1 : res);

    }
    return 0;
}