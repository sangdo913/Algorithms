#include<iostream>
#include<stdlib.h>
#include<cstdio>

using namespace std;

int n;
int m;

int isfriend[10][10];
int flen[10];

int connect(int visit, int i){
    if(i == n) {
        return 1;
    }

    if(visit & (1<< i)){
        return connect(visit, i+1);
    }
    int ret = 0;
    
    for(int j = 0; j < flen[i]; ++j){
        int fid = isfriend[i][j];
        if(!(visit&(1<<fid))){ ret += connect(visit | (1<<i) | (1 << fid), i+1); }
    }
    return ret;
}

int main(){
    freopen("0Text.txt", "r", stdin);

    int c;
    scanf("%d", &c);
    
    while(c--){
        scanf("%d %d", &n, &m);
        for(int i = 0; i < n; ++i) flen[i] = 0;

        while(m--){
            int a,b;
            
            scanf("%d %d", &a, &b);
            isfriend[a][flen[a]++] = b;
            isfriend[b][flen[b]++] = a;
        }
        printf("%d\n", connect(0,0));
    }
    
    return 0;
}