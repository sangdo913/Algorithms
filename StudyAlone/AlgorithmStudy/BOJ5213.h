#include<cstdio>
#include<queue>
using namespace std;
struct TILE{
    int l, r;
    int num;
    int tnum;
    TILE(){
        l = r = -1;
    }
};

TILE tile[502][502];
bool visit[502][520];
struct INFO{
    int r, c, num, tnum, pnum;
};

int dr[8] = {-1,1,1,-1,1,-1,0,0};
int dc[8] = {0,0,1,1,-1,-1,-1,1};
bool adj[502][502][8];
int path[250010];
int st[250000], top;
int BOJ5213(){
    int n;
    int cnt = 1;
    scanf("%d\n", &n);
    for(int i = 1; i <= n; i++){
        for(int j = 1; j <= n - 1 + (i&1); j++){
            scanf("%d %d\n", &tile[i][j].l, &tile[i][j].r);
            tile[i][j].num = i;
            tile[i][j].tnum = cnt++;
        }
    }

    for(int i = 1; i <= n; i++){
        for(int j = 1; j <=n - 1 + (i&1); j++){
            for(int d = 0; d < 8; d++){
                int nr = i + dr[d];
                int nc = j + dc[d];
                if(tile[nr][nc].l == -1) continue;
                switch(d){
                    case 2:
                    case 3:
                    if((i&1) == 0){
                        adj[i][j][d] = tile[i][j].r == tile[nr][nc].l;
                    }
                    break;
                    case 0:
                    case 1:
                    if((i&1)){
                           adj[i][j][d] = tile[i][j].r == tile[nr][nc].l; 
                    }
                    else{
                        adj[i][j][d] = tile[i][j].l ==tile[nr][nc].r;
                    }
                    break;
                    case 4:
                    case 5:
                    if((i&1)){
                        adj[i][j][d] = tile[i][j].l == tile[nr][nc].r;
                    }
                    break;
                    case 6:
                    adj[i][j][d] = tile[i][j].l ==  tile[nr][nc].r;
                    break;
                    case 7:
                    adj[i][j][d] = tile[i][j].r == tile[nr][nc].l;
                    break;
                }

            }
        }
    }

    int max = 0;
    int finalpath;
    queue<INFO> que;
    INFO info;
    info.r = 1;
    info.c = 1;
    info.tnum  = 1;
    info.num = 1;
    info.pnum = 1;

    que.push(info);
    path[1]= 0;
    int pathnum;

    visit[1][1] = true;
    while(!que.empty()){
        INFO now = que.front();
        que.pop();
        if(now.tnum == (n*n - n/2)){
            max = now.num;
            finalpath = now.tnum;
            break;
        }

        if(max <= now.num){
            pathnum = now.pnum < pathnum ? now.pnum : pathnum;
            finalpath = now.tnum;
            max = now.num;
        }

        for(int d = 0; d < 8; d++){
            int nr = now.r + dr[d];
            int nc = now.c + dc[d];

            if(adj[now.r][now.c][d]){
                INFO next;
                next.r = nr;
                next.c = nc;
                next.num = nr;
                next.tnum = tile[nr][nc].tnum;
                next.pnum = now.pnum+1;
                if(visit[nr][nc]) continue;
                visit[nr][nc] = true;
                path[next.tnum] = now.tnum;
                
                que.push(next); 
            }
        }

    }
        int p = finalpath;
        while(p){
            st[top++] = p;
            p = path[p];
        }
        printf("%d\n", top);
        while(top){
            printf("%d ", st[--top]);
        }
        printf("\n");
    return 0;
}