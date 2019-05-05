#include<iostream>
#include<queue>
#include<vector>

using namespace std;

struct COD{
    int r, c;
};

int gnum = 1, n, m;
int dr[4] = {-1,1,0,0};
int dc[4] = {0,0,-1,1};
int group[1000][1000];
int gsize[1000000];
char arr[1000][1001], res[1000][1001];

queue<COD> que;

void makeGroup(int r, int c){
    COD now = {r,c}, next;
    que.push(now);

    group[r][c] = gnum;

    while(que.size()){
        now = que.front(); que.pop();
        gsize[gnum]++;
        
        for(int d = 0; d <4; d++){
            next.r = now.r + dr[d], next.c = now.c + dc[d];
            if(next.r < 0 || next.c < 0 || next.r >= n || next.c >= m) continue;
            if(arr[next.r][next.c] == '1') continue;
            if(group[next.r][next.c]) continue;
            group[next.r][next.c] = gnum;
            que.push(next);
        }
    }
    gnum++;
}

int chk[1000000];


#define MAX(x,y) ((x) > (y) ? (x) : (y))

int Do(){
    ios_base::sync_with_stdio(false), cin.tie(0), cout.tie(0);
    cin >> n >> m;

    for(int i = 0; i < n; i++) cin >> arr[i];
    
    for(int i = 0; i < n; i++) for(int j = 0;j  < m ; j++){
        if(arr[i][j] == '0' && group[i][j] == 0) makeGroup(i,j);
    }

    int ch = 1;
    for(int i = 0; i < n; i++) for(int j = 0; j < m; j++){
        if(arr[i][j] == '1'){
            int t = 1;
            for(int d = 0; d < 4 ; d++){
                int nr = i + dr[d], nc = j + dc[d];
                if(nr < 0 || nc < 0 || nr >= n || nc >= m) continue;
                if(chk[group[nr][nc]] == ch) continue;
                chk[group[nr][nc]] = ch;
                t += gsize[group[nr][nc]];
            }
            res[i][j] = (t%10) + '0';
            ch++;
        }
        else res[i][j] = '0';
    }

    for(int i = 0; i < n; i++) cout << res[i] << '\n';
    return 0;
}