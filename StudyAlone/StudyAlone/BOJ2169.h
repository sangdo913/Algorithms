#include<iostream>
#include<cstring>

using namespace std;

const int dr[] = {0,0,1};
const int dc[] = {-1,1,0};
int rev[3] = {1,0,3}, n, m;

int dist[1000][1000][3];
int arr[1000][1000];

int dfs(int r, int c, int prev){
    int &ret = dist[r][c][prev];
    if(r == n-1 && c == m-1) ret = arr[r][c];
    if(ret != 0x3f3f3f3f) return ret;
    ret = -0x3f3f3f3f;

    for(int d = 0; d < 3; d++){
        if(d == rev[prev]) continue;
        int next[2] = {r + dr[d], c + dc[d]}; 
        if(next[0] < 0 || n == next[0] || next[1] == m || next[1] < 0)continue;
        int num = dfs(next[0], next[1], d);
        ret = num+ arr[r][c] > ret ? num + arr[r][c] : ret; 
    }
    ret = ret == -0x3f3f3f3f ? -0x3f3f3f3f : ret;

    return ret;
}

int Do(){
    ios_base::sync_with_stdio(false), cin.tie(0), cout.tie(0);

    cin >> n >> m;

    for(int i = 0; i < n; i++) for(int j = 0 ; j < m; j++) cin >>arr[i][j];
    int res = -0x3f3f3f3f;
    memset(dist,0x3f,sizeof(dist));

    cout << dfs(0,0,2);
    return 0;
}