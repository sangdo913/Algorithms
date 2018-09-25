#include<iostream>
#include<queue>
#include<algorithm>
#include<cstring>

using namespace std;

int map[15][12], n, h, w;
int temp[15][12];

queue<int> del;

int MIN(int i1, int i2){return i1 < i2 ? i1 : i2;}

int dr[4] = {-1,1,0,0};
int dc[4] = {0,0,-1,1};

void down(){
    int st[15], top = 0;
    for(int j = 0; j < w; j++){
        top = 0;
        int i = 0;
        for(; i < h; i++){
            if(temp[i][j]){
                st[top++] = temp[i][j];
                temp[i][j] = 0;
            }
        }
        i--;
        while(top){
            temp[i][j] = st[--top];
            i--;
        }
    }
}

int cal(int c){
    queue<pair<int, int> > bomb;
    bool visit[15][12] = {};

    for(int i = 0; i < h; i++){
        if(temp[i][c]){
            bomb.push(make_pair(i,c));
            visit[i][c] = true;
            break;
        }
    }

    int boom = 0;

    while(bomb.size()){
        pair<int, int> now = bomb.front();
        bomb.pop();
        boom++;

        int x[2], y[2];

        int d = temp[now.first][now.second];
        temp[now.first][now.second] = 0;

        x[0] = now.second -d + 1;
        x[0] = x[0] < 0 ? 0 : x[0];
        x[1] = now.second + d;
        x[1] = x[1] > w ? w : x[1];

        y[0] = now.first -d + 1;
        y[1] = now.first + d;
        y[0] = y[0] < 0 ? 0 : y[0];
        y[1] = y[1] > h ? h : y[1];

        for(int j = x[0]; j < x[1]; j++){
            if(visit[now.first][j]) continue;
            visit[now.first][j] = true;

            if(temp[now.first][j]) bomb.push(make_pair(now.first,j));
        }

        for(int j = y[0]; j < y[1]; j++){
            if(visit[j][now.second]) continue;
            visit[j][now.second] = true;

            if(temp[j][now.second] ) bomb.push(make_pair(j,now.second));
        }
    }
    down();
    return boom;
}

int boom(int depth, int bn){
    if(depth == n) return bn;

    int restore[15][12];

    memcpy(restore, temp, sizeof(temp));
    
    int res = 0x3f3f3f3f;
    for(int i = 0; i < w; i++){
        int num = cal(i);
        res = MIN(res, boom(depth+1, bn - num));
        memcpy(temp, restore, sizeof(temp)); 
    }        

    return res;
}

int SWEA5656(){
    int t;
    cin >> t;
    for(int tc= 1; tc<=t;tc++){
        cin >> n >> w >> h;
        int bn = 0;
        for(int i = 0; i < h; i++){
            for(int j = 0; j < w; j++){
                cin >> temp[i][j];
                bn += temp[i][j] > 0;
            }
        }

        cout << '#' << tc << ' ' << boom(0,bn) << '\n';
    }
    return 0;
}