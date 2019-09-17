#include<iostream>

using namespace std;

int h,w;
char arr[20][21];
int dr[4][3] = {{0,1,1}, {0,0,1},{0,0,1},{0,1,1}};
int dc[4][3] = {{1,0,1},{0,1,0},{0,1,1},{0,0,1}};
int bnum;

bool check(int b, int i, int j){
    int r, c;
    for(int d = 0; d < 3; ++d){
        r = i + dr[b][d], c = j + dc[b][d];
        if(r < 0 || h <= r || c < 0 || w <= c) return false;
        if(arr[r][c] == '#') return false;
    }
    return true;
}

void mark(int b, int i, int j, char v){
    int r, c;
    for(int d = 0; d < 3; ++d){
        r = i+dr[b][d], c = j + dc[b][d];
        arr[r][c] = v;
    }
}

int dfs(int i,int j, int cnt){
    if(!cnt) return 1;
    if(i == h) return 0;
    int nr = i, nc =j+1;
    if(nc == w) ++nr, nc = 0;

    int ret = 0;

    if(arr[i][j] =='#'){
        if(check(0,i,j)){
            mark(0,i,j,'#');
            ret += dfs(nr,nc, cnt-3);
            mark(0,i,j,'.');
        }
        ret += dfs(nr,nc,cnt);
    }
    else{
        for(int d = 1; d < 4; ++d){
            if(check(d,i,j)){
                mark(d,i,j,'#');
                ret += dfs(nr,nc,cnt-3);
                mark(d,i,j,'.');
            }
        }
    }

    return ret;
}

int main(){
    freopen("0Text.txt", "r" ,stdin);

    int c;
    scanf("%d\n", &c);

    while(c--){
        bnum = 0;
        scanf("%d %d", &h, &w);
        for(int i = 0; i < h; ++i) for(int j = 0; j < w; ++j){
            scanf(" %c ", arr[i] + j);
            if(arr[i][j] == '.'){
                bnum++;
            }
        }
        printf("%d\n", dfs(0,0,bnum));
    }
}