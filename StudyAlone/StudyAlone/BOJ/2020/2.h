#include<iostream>
#include<queue>
using namespace std;

struct POS{
    int r,c;
    int type;
};

int n, m, r,g;
int mymap[50][50];
int backupmap[50][50];
int gettime[3][50][50];
int tc;
int dr[4] = {-1,1,0,0};
int dc[4] = {0,0,-1,1};

int simulate(){
    tc++;
    queue<POS>Q;
    for(int i = 0; i < n; ++i) for(int j = 0; j < m; ++j) {
        gettime[2][i][j] = gettime[1][i][j] = 0x3f3f3f3f;
        if(mymap[i][j] < 0){
            Q.push({i,j,mymap[i][j]});
            gettime[-mymap[i][j]][i][j] = 0;
        }
    }
    
    int res = 0;
    int t = 0;
    while(!Q.empty()){
        int cnt = Q.size();
        t++;

        while(cnt--){
            POS now = Q.front(); Q.pop();
            if(gettime[1][now.r][now.c] == gettime[2][now.r][now.c]){
                res++; 
                continue;
            }
            POS next;
            for(int d = 0; d < 4; ++d){
                next = {now.r +dr[d], now.c + dc[d],now.type};
                if(next.r < 0 || next.r >= n || next.c < 0 || next.c >= m ) continue;
                if(mymap[next.r][next.c] == 0) continue;
                if(gettime[-now.type][next.r][next.c] <= t) continue;
                gettime[-now.type][next.r][next.c] = t;
                if(mymap[next.r][next.c] > 0) {
                    mymap[next.r][next.c] = now.type;
                    Q.push(next);
                }
            }
        }
    }
    return res;
}

int getRES(int i, int j , int r, int c){
    int nj = j + 1, ni = i;
    if(r == 0 && c == 0) {
        for(int i = 0; i < n; ++i) for(int j= 0; j < m; ++j) mymap[i][j] = backupmap[i][j];
        return simulate();
    }
    if(i == n) return 0;
    if(nj == m) {
        nj = 0; ++ni; 
    }
    int res = 0;
    if(backupmap[i][j] == 2){
        if(r > 0){
            backupmap[i][j] = -1;
            res = getRES(ni,nj, r-1, c);
            backupmap[i][j] = 2;
        }
        if(c > 0){
            backupmap[i][j] = -2;
            int res2 = getRES(ni,nj, r, c-1);
            res = res < res2 ? res2 : res;
            backupmap[i][j] = 2;
        }
    }
    int res2 = getRES(ni,nj,r,c);
    res = res < res2 ? res2 : res;
    return res;
}

int main(){
    freopen("0Text.txt", "r", stdin);
    cin >> n >> m >> g >> r;
    for(int i = 0; i < n; ++i){
        for(int j = 0; j < m; ++j) cin >> backupmap[i][j];
        }
    cout << getRES(0,0,g,r);

    return 0;
}