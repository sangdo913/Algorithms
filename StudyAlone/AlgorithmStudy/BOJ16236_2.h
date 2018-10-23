#include<iostream>
#include<queue>
#include<cstring>
using namespace std;

struct COD{
    int r,c, cnt;
};
struct FISH{
    COD p;
    int size;
    int remain;
    FISH():size(2), remain(2), p({0,0}){}
    FISH(COD p) : p(p){}

    void eat(){
        remain--;
        if(remain == 0){
            size++;
            remain = size;
        }
    }
};

struct cmp{
    bool operator()(COD c1, COD c2){
        if(c1.r == c2.r){
            return c1.c < c2.c;
        }
        return c1.r < c2.r;
    }
};

bool visit[10][10];
int mm[10][10];
int n;
bool isout(int r, int c){
    return r< 0 || c < 0 || r >= n || c >= n;
}
int dr[4] = {-1,1,0,0};
int dc[4] = {0,0,-1,1};


queue<COD> que;
bool ff(FISH &f){
    COD now  = f.p;
    priority_queue<COD, vector<COD>, cmp> pq;
    memset(visit, false, sizeof(visit));
    visit[now.r][now.c] = true;
    bool isfind = false;
    while(que.size()){
        int cnt = que.size();
        while(cnt--){
            now = que.front();
            if(mm[now.r][now.c] < f.size){
                isfind  =true;
                pq.push(now);
                continue;
            }

            for(int d = 0; d < 4; d++){
                COD next = now;
                next.r += dr[d];
                next.c+=dc[d];

                if(isout(next.r,next.c)) continue;
                if(visit[next.r][next.c]) continue;
                if(mm[next.r][next.c] > f.size) continue;

                que.push(next);
            }
        }
        if(isfind) break;
    }
}

int BOJ16236(){
    cin >> n;
    FISH f;
    for(int i =0 ; i< n; i++){
        for(int j = 0; j < n; j++){
            cin >> mm[i][j];
            if(mm[i][j] == 9){
                f.p.r = i;
                f.p.c = j;
                mm[i][j] = 0;
            }
        }
    }
    return 0;
}