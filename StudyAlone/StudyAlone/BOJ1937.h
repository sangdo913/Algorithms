#include<iostream>

using namespace std;

int dr[4] = {0,1,-1,0};
int dc[4] = {1,0,0, -1};

int dist[500][500],n;
int arr[500][500];

int dfs(int r, int c){
    int &ret = dist[r][c];
    if(ret) return ret;

    for(int d = 0; d < 4; d++){
        int nr = r +dr[d], nc = c + dc[d];
        if(nr < 0 || nc < 0 || nr ==n || nc == n) continue;
        if(arr[r][c] < arr[nr][nc]){
            int res = dfs(nr,nc);
            ret = ret > res ? ret : res;
        }
    }

    return ++ret;
}

int Do(){
    ios_base::sync_with_stdio(false), cin.tie(0), cout.tie(0);

    cin >> n;
    for(int i = 0; i < n; i++) for(int j = 0; j < n; j++){
        cin >> arr[i][j];
    }

    int res = 0;

    for(int i = 0; i < n; i++) for(int j = 0;j < n; j++){
        int t = dfs(i,j);
        res = res  > t ? res : t;
    }
    cout << res;
    return 0;
}