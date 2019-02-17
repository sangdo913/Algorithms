#include<iostream>
#include<queue>
#include<cstring>

using namespace std;

char arr[50][51];
bool visit[50][50];

int n,m;

int dr[4] = {-1,1,0,0};
int dc[4] = {0,0,-1,1};

bool dfs(int r, int c, int br, int bc){
    if(visit[r][c]) return true;
    visit[r][c] = true;

    for(int d = 0; d < 4 ;d++){
        int nr = r + dr[d];
        int nc = c + dc[d];

        if(nr < 0 || c < 0 || nr >= n || nc >= m) continue;
        if(nr == br && nc == bc) continue;
        if(arr[r][c] != arr[nr][nc]) continue;
        if(dfs(nr,nc,r,c)) return true;
    }

    return false;
}

int Do(){
    cin >> n >> m;

    for(int i = 0; i < n; i++){
        cin >> arr[i];
    }

    int vis = 1;
    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            if(visit[i][j]) continue;
            if(dfs(i,j,-1,-1)) return !(cout <<"Yes");
        }
    }

    return !(cout << "No");
}