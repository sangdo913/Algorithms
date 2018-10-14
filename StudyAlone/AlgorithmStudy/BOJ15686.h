#include<iostream>

using namespace std;

int map[50][50];
int m;

int h[100][2];
int cp[13][2];
int ccnt;
int hcnt;

int ABS(int i){ return i > 0 ? i : -i; }
int MIN(int i1, int i2){return i1 < i2 ? i1 : i2;}

int len(int visit){
    int res = 0; 
    int idx = 0;
    while(visit){
        if(visit&1){
            int dist = 0x3f3f3f3f;
            for(int i = 0; i < hcnt; i++){
                int temp = ABS(h[i][0] - cp[idx][0]) + ABS(h[i][1] - cp[idx][0]);
                dist = MIN(dist, temp);
                
            }
            res += dist;
        }
        visit>>=1;
        idx++;
    }
    return res;
}

int comb(int len, int choose, int visit){
    if(choose == m){
        return len;
    }
    if(len > hcnt) return 0x3f3f3f3f;
    
    int res = 0x3f3f3f3f;
    res = comb(len+1, choose, visit);
    visit |= 

    
}