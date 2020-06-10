#include<iostream>

using namespace std;
int n, m,k;
struct SHARK{
    bool gone;
    int x,y, i, d;
}sharks[401];
SHARK smell[1002][400];
int len[1001];
int preferd[400][5][4];
int mymap[1001][20][20];
int svisit[20][20];
enum DIR{N, U,D, L, R,SIZE};
int dr[5] = {0,-1,1,0,0};
int dc[5] = {0,0,0,-1,1};

int main(){
    freopen("0Text.txt", "r", stdin);
    cin >> n >> m >> k;
    int cnt = 0;
    for(int i = 0; i < n; ++i){
        for(int j = 0; j < n; ++j){
            int shark;
            cin >> shark;
            if(shark){
                sharks[shark].x = i, sharks[shark].y = j;
                smell[0][len[0]].i = shark;
                smell[0][len[0]].x = i;
                smell[0][len[0]++].y = j;
            }
        }
    }
    for(int i = 1; i <= m; ++i){
        cin >> sharks[i].d; 
    }
    for(int i = 1; i <= m; ++i){
        for(int d = 1; d < SIZE; ++d){
            for(int j = 0; j < 4; ++j){
                cin >> preferd[i][d][j];
            }
        }
    }
    cnt = 0;
    int remain = m;
    while(cnt < 1000 && remain > 1){
        cnt++;
        for(int i = 1; i <= k && cnt- i >= 0; ++i){
            for(int id = 0; id < len[cnt-i]; ++id){
                int x = smell[cnt-i][id].x;
                int y = smell[cnt-i][id].y;
                mymap[cnt][x][y] = smell[cnt-i][id].i;
            }
        }

        for(int id = 1; id <= m; ++id){
            SHARK &s = sharks[id];
            if(s.gone) continue;
            int nosmell = -1;
            int smell = -1;
            for(int d = 0; d < 4; ++d){
                int nd = preferd[id][s.d][d];
                int nx = s.x + dr[nd];
                int ny = s.y + dc[nd];
                if(nx < 0 || nx == n || ny < 0 || ny == n) continue;
                if(mymap[cnt][nx][ny] == 0) {
                    nosmell = nd;
                    break;
                }
                else if(mymap[cnt][nx][ny] == id && smell == -1){
                    smell = nd;
                }
            }
            if(nosmell == -1) nosmell = smell;
            s.d = nosmell;
            s.x += dr[s.d];
            s.y += dc[s.d];
            if(svisit[s.x][s.y] == cnt){
                remain--;
                s.gone = 1;
            }
            else svisit[s.x][s.y] = cnt;
        }
        for(int id = 1; id <= m; ++id){
            SHARK &s  = sharks[id];
            if(!s.gone){
                smell[cnt][len[cnt]].i = id;
                smell[cnt][len[cnt]].x = s.x;
                smell[cnt][len[cnt]++].y = s.y;
            }
        }
    }
    if(remain == 1) cout << cnt;
    else cout << -1;

    return 0;
}