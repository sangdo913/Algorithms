#include<iostream>
#include<queue>

struct INFO{
    int r, c;
};

using namespace std;
int visit[50][50];
char mymap[50][51];
int dr[4] = {-1,1,0,0};
int dc[4] = {0,0,-1,1};

int main(){
    freopen("0Text.txt" ,"r", stdin);
    int tc;
    int n, m;
    cin >> n >> m;
    for(int i = 0; i < n; ++i){
        cin >> mymap[i];
    }
    queue<INFO> Q;

    int res = 0;
    for(int i = 0; i < n; ++i){
        for(int j = 0; j < m; ++j){
            if(mymap[i][j] == 'W') continue;
            tc++;

            visit[i][j] = tc;
            Q.push({i,j});

            int dist = 0;
            while(Q.size()){
                int cnt = Q.size();
                while(cnt--){
                    INFO now = Q.front(); Q.pop();
                    if(res < dist) res = dist;
                    for(int d = 0; d < 4; ++d){
                        int nr = now.r + dr[d];
                        int nc = now.c + dc[d];

                        if(nr < 0 || nc < 0 || nr == n || nc == m) continue;
                        if(mymap[nr][nc] == 'W')continue;
                        if(visit[nr][nc] == tc) continue;
                        visit[nr][nc] = tc;
                        Q.push({nr,nc});
                    }
                }
                dist++;
            }
        }
    }
    cout << res;
    return 0;
}