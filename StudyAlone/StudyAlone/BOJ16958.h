#include<iostream>
#include<queue>
#include<algorithm>
#include<cstring>

using namespace std;

struct COD{
    int r,c, type;
};

COD info[1001];
int n, m, t;

#define ABS(x) ((x) > (0) ? (x) : (-(x)))
#define MIN(x,y) ((x) > (y) ? (y) : (x))

int getDist(int f, int to){
    int d1 , d2;
    d1 = d2 = 0x3f3f3f3f; 

    if(info[f].type == 1 && info[to].type == 1) d1 = t;
    else if(info[f].type == 1 && info[to].type == 0){
        for(int i =1 ; i <= n; i++){
            if(info[i].type == 1){
                int td = t + ABS(info[i].r - info[to].r) +ABS(info[i].c - info[to].c);
                d1 = MIN(d1, td);
            }
        }
    }
    else if(info[f].type == 0 && info[to].type == 1){
        for(int i = 1; i <= n; i++){
            if(info[i].type == 1){
                int td = t + ABS(info[i].r - info[f].r) +ABS(info[i].c - info[f].c);
                d1 =  MIN(d1, td);
            }
        }
    }
    else if(info[f].type == 0 && info[to].type == 0){
        int td1 =0x3f3f3f3f, td2 = 0x3f3f3f3f;
        for(int i = 1; i <= n; i++){
            if(info[i].type == 0) continue;
            int td = ABS(info[i].r - info[f].r) + ABS(info[i].c - info[f].c);
            td1 = MIN(td1, td);
        }

        for(int i = 1; i <= n; i++){
            if(info[i].type == 0) continue;
            int td = ABS(info[i].r - info[to].r) + ABS(info[i].c - info[to].c);
            td2 = MIN(td, td2);
        }

        d1 = t + td1 + td2;
    }
    d2 = ABS(info[f].r - info[to].r)  + ABS(info[f].c - info[to].c);
    d1 = MIN(d1, d2);
    return d1;
}

int Do(){
    cin >> n >>  t;

    for(int i = 1; i <= n; i++){
        cin >> info[i].type >> info[i].r >> info[i].c;
    }

    cin >> m;
    
    while(m--){
        int f ,to;
        cin >> f >> to;
        cout << getDist(f,to) << '\n';
    }
    return 0;
}