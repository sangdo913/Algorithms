#include<cstdio>
#include<cstring>
int sc = 0, pcnt = 0;
int people[10][2];
int T[2];
int abs(int i){return i > 0 ? i : -i;}
int MAX(int i1, int i2){return i1 < i2 ? i1 : i2;}

struct Stair{
    int downp[3], now, wait, t;
    int pos[2];
    int arriveTime[100], cnt;
    int complete;

    int getDistance(int r, int c){
        return abs(r - pos[0]) + abs(c - pos[1]);
    }
    void init(int idx, int bit){
        for(int i = 0; i < 3; i++) downp[i] = 0;
        memset(arriveTime, 0 ,sizeof(arriveTime));
        wait = 0;
        now = 0;
        t = T[idx];
        int res = 0;
        complete = 0;
        for(int i = 0; i < pcnt; i++){
            if((bit&1) == idx){
                int at = abs(people[res][0] -pos[0]) + abs(people[res][1] -pos[1]);
               arriveTime[at]++;
            }
            res++;
            bit>>=1;
        }
    }
    void godown(){
       for(int i = 0 ; i < 3; i++){
           downp[i]--;
           if(downp[i] == 0) complete++;
       }
    }
    bool check(){
        for(int i = 0; i < 3; i++){
            if(wait && downp[i] <= 0){
                wait--;
                downp[i] = t;
            }
        }
        return downp[now] <=0;
    }
    void arrive(int ti){
        wait+= arriveTime[ti];
    }
    void process(int ti){
        godown();
        check();
        arrive(ti);
    }
    bool isEnd(){
        bool empty = true;
        for(int i = 0; i < 3; i++) {empty &= downp[i] <= 0;}
        return wait == 0 && empty;
    }
} stair[2];

int getTime(int bit){
   int res = 0;
   
   stair[0].init(0, bit);
   stair[1].init(1, bit);
    int ti = 0;
    while(stair[0].complete + stair[1].complete != pcnt){
        stair[0].process(ti);
        stair[1].process(ti);
        ti++;
    }
    return --ti;
}

int Lunch(){
    int t;
    scanf("%d\n", &t);

    for(int tc = 1; tc <= t; tc++){
        int n;
        scanf("%d\n", &n);
        sc = pcnt = 0;

        for(int i = 0; i < n; i++){
            for(int j = 0; j < n; j++){
                int in;
                scanf("%d\n", &in);
                if(in == 1) {
                    people[pcnt][0] = i;
                    people[pcnt++][1] = j;
                }
                else if(in){
                    stair[sc].pos[0] = i;
                    stair[sc].pos[1] = j;
                    T[sc++] = in;
                }
            }
        }
        int res = 100000;
        for(int bit = 0; bit < 1 << pcnt; bit++){
            res = MAX(res, getTime(bit));
        }
        printf("#%d %d\n", tc, res);
    }
    return 0;
}