#include<iostream>
#include<queue>
#include<cstring>

using namespace std;

int arr[5][5][5];
const int dx[] = {-1,1,0,0,0,0};
const int dy[] = {0,0,-1,1,0,0};
const int dz[] = {0,0,0,0,-1,1};

void rotate(int id){
    int temp[5][5];
    for(int i = 0; i < 5; i++){
        for(int j = 0; j < 5; j++){
            temp[j][4-i] = arr[id][i][j];
        }
    }
    memcpy(arr[id], temp, sizeof(temp));
}

int res = 0x3f3f3f3f;
#define MIN(x,y) ((x) > (y) ? (y) : (x))
int visit[5][5][5];
int ch = 1;

bool isout(int x){
    return x < 0 || x >= 5;
}

void bfs(){
    if(arr[0][0][0] == 0 || arr[4][4][4] == 0) return;
    ch++;
    queue<int> que;
    que.push(0);
    visit[0][0][0] = ch;

    int cnt = 0;
    int t = 0;
    while(que.size()){
        cnt = que.size();
        while(cnt--){
            int now = que.front(); que.pop();
            int x = now&0b111; now >>=3;
            int y = now & 0b111; now>>=3;
            int z = now & 0b111; now>>=3;

            if(x == 4 && y == 4 && z == 4) {
                res = MIN(res,t);
                return; 
            }

            for(int d = 0; d < 6; d++){
                int nx = x + dx[d];
                int ny = y + dy[d];
                int nz = z + dz[d];

                if(isout(nx) || isout(ny) || isout(nz)) continue;
                if(visit[nx][ny][nz] == ch) continue;
                if(arr[nx][ny][nz] == 0) continue;
                visit[nx][ny][nz] = ch;
                int next = (nz << 6) | (ny << 3) | nx;
                que.push(next);
            }
        }
        t++;
        if(t > res) return;
    }
}

int temp[5][5];

void permu(int l){
    if(l == 5){
        bfs();
        return;
    }

    for(int i = l; i < 5; i++){
        memcpy(temp, arr[i], sizeof(temp));
        memcpy(arr[i], arr[l], sizeof(temp));
        memcpy(arr[l], temp, sizeof(temp));
        permu(l+1);
        memcpy(temp, arr[i], sizeof(temp));
        memcpy(arr[i], arr[l], sizeof(temp));
        memcpy(arr[l], temp, sizeof(temp));
    }
}

void dfs(int i){
    if(i == 5){
        permu(0);
        return;
    }

    for(int j = 0; j < 4; j++) rotate(i), 
        dfs(i+1);
}

int Do(){
    ios_base::sync_with_stdio(false), cin.tie(0), cout.tie(0);

    for(int i = 0; i < 5; i++){
        for(int j = 0; j < 5; j++){
            for(int k = 0; k < 5; k++){
                cin >> arr[i][j][k];
            }
        }
    }
    dfs(0);
    cout << (res == 0x3f3f3f3f ? -1 : res);
    return 0;
}