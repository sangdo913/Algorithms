#include<iostream>
#include<vector>

using namespace std;

vector<int> vec[2];
int info[100][2];
int ilen, n;

int check[10][10];
int dr[4] = {-1,-1,1,1};
int dc[4] = {-1,1,-1,1};

void Put(int r, int c, int flag){
    for(int d = 0; d  < 4; d++){
        int nr = r;
        int nc = c;
        while(0<= nr && nr < n && 0 <= nc && nc < n){
            check[nr][nc] += flag;
            nr += dr[d];
            nc += dc[d];
        }
    }
}

int MAX[2];

void dfs(int idx, int now, int cnt){
    if(now == vec[idx].size()){
        MAX[idx] = MAX[idx] > cnt ? MAX[idx] : cnt;
        return;
    }

    int r = info[vec[idx][now]][0];
    int c = info[vec[idx][now]][1];

    if(check[r][c] == 0){
        Put(r,c,1);
        dfs(idx, now+1, cnt+1);
        Put(r,c,-1);
    }

    dfs(idx, now+1, cnt);
}

int Do(){
    cin >> n;
    for(int i = 0; i < n; i++){
        for(int j = 0; j<n; j++){
            int in;
            cin >> in;

            info[ilen][0] = i;
            info[ilen][1] = j;

            if(in == 1){
                vec[(i&1) ^ (j&1)].push_back(ilen++);
            }
        }
    }
    dfs(0,0,0); dfs(1,0,0);

    cout << MAX[0] + MAX[1];
    return 0;
}