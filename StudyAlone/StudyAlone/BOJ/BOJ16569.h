#include<iostream>
#include<queue>
#include<vector>

using namespace std;
struct INFO{
    int r,c;
    int type;
};
int mymap[100][100];
int n, m,v;
int mr, mc;
vector<INFO> times[201];
int visit[100][100];
int dr[4] = {-1,1,0,0};
int dc[4] = {0,0,-1,1};

int main(){
    freopen("0Text.txt", "r", stdin);
    cin >> n >> m >> v;
    cin >> mr >> mc;
    mr--, mc--;
    for(int i = 0; i < n;++i){
        for(int j = 0; j < m; ++j){
            cin >> mymap[i][j];
        }
    }
    for(int i = 0; i < v; ++i){
        int r, c, x;
        cin >> r >> c >> x;
        --r,--c;
        times[x].push_back({r,c});
        mymap[r][c] = -2;
    }

    queue<INFO> Q;
    Q.push({mr,mc,0});
    visit[mr][mc] = 1;
    int t = 0;
    int res = 0;
    int rest;

    while(!Q.empty()){
        if(t <= 200){
            for(int i = 0; i < times[t].size(); ++i){
                Q.push({times[t][i].r, times[t][i].c, 1});
                mymap[times[t][i].r][times[t][i].c] = -1;
            }
        }
        // cout << t <<endl;
        // for(int i = 0;  i< n; ++i){
        //     for(int j = 0; j < m; ++j) cout << mymap[i][j] << ' ' ;
        //     cout << endl;
        // }
        // cout << "============================\n";
        int cnt = Q.size();
        while(cnt--){
            INFO now = Q.front(); Q.pop();
            if(now.type == 0){
                if(mymap[now.r][now.c] == -1) continue;
                if(res < mymap[now.r][now.c]){
                    res = mymap[now.r][now.c];
                    rest = t;
                }
            }

            INFO next;

            for(int d= 0 ;d < 4; ++d){
                next.r = now.r + dr[d];
                next.c = now.c + dc[d];
                next.type = now.type;

                if(next.r < 0 || next.r >= n || next.c < 0 || next.c >= m) continue;
                if(now.type == 0 && visit[next.r][next.c]) continue;
                if(mymap[next.r][next.c] == -1) continue;
                if(now.type == 0) {
                    if(mymap[next.r][next.c] == -2) continue;
                    visit[next.r][next.c] =1;
                }
                else mymap[next.r][next.c] = -1;
                Q.push(next);
            }
        }

        t++;
    }

    cout << res << ' ' << rest;
    
    return 0;
}