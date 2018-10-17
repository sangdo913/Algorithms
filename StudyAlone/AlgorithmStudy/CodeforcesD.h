#include<iostream>
#include<queue>
#include<cstring>

using namespace std;

int r,c;
int n,m;
int x, y;

struct INFO{
    int r, c, l,R;
};
int res = 0;
char map[2001][2001];
int visit[2001][2001][2];
bool cango[2001][2001];
int dr[4] = {-1,1,0,0};
int dc[4] = {0,0,-1,1};
int MAX(int i1, int i2){return i1 < i2 ? i2 : i1;}
bool isout(int r, int c){
    return r < 1 || c < 1 || r > n || c > m;
}

bool checklr(INFO &i){
    bool res = visit[i.r][i.c][0] < i.l || visit[i.r][i.c][1] < i.R;
    visit[i.r][i.c][0] = MAX(visit[i.r][i.c][0], i.l);
    visit[i.r][i.c][1] = MAX(visit[i.r][i.c][1], i.R);
    return res;
}

bool iswall(INFO &i){
    return map[i.r][i.c] == '*';
}

int bfs(){
    INFO now = {r,c,x,y}; 
    visit[r][c][0] = now.l;
    visit[r][c][1] = now.r;
    queue<INFO > Q;
    Q.push(now);

    int res = 0;

    while(Q.size()){
        now = Q.front();
        Q.pop();
        cango[now.r][now.c] = true;
        
        INFO next = now;
        next.r +=1;
        if(!isout(next.r, next.c)&& !iswall(next)){
           if(checklr(next)){
               Q.push(next);
           } 
        }
        next = now;
        next.r -=1;
        if(!isout(next.r, next.c) && !iswall(next)){
            if(checklr(next)){
                Q.push(next);
            }
        }

        next = now;
        next.c -= 1;
        if(!isout(next.r,next.c) && next.l && !iswall(next)){
            next.l--;
            if(checklr(next)) Q.push(next);
        }

        next = now;
        next.c += 1;
        if(!isout(next.r,next.c) && next.R && !iswall(next)){
            next.R--;
            if(checklr(next)) Q.push(next);
        }
    }

    for(int i = 1; i <= n; i++){
        for(int j = 1; j <= m; j++){
            res += cango[i][j];
        }
    }
    return res;
}
int CodeforcesD(){
    cin >> n >> m >>r >> c >> x >> y;
    memset(visit, -1, sizeof(visit));
    for(int i = 1; i <= n ; i++){
        cin >> map[i]+1;
    }

    cout << bfs();
    return 0;
}