#include<iostream>
#include<queue>

using namespace std;

struct COD{
    int r,c, t;
};

queue<COD> que;
int dr[4] = {-1,1,0,0};
int dc[4] = {0,0,-1,1};
int ddr[2] =  {0,1}, arr[1000][1000];
int ddc[2] = {1,0}, m , n , h,w , sr, sc,fr,fc;
int gob[4];
bool visit[1000][1000];

int Do(){
    ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    cin >> n >> m;

    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            cin >> arr[i][j];
        }
    }

    cin >> h >> w >> sr >> sc >> fr >> fc;
    --sr, --sc, --fr, --fc;
    gob[0] = 1, gob[1] = h, gob[2] = 1, gob[3] = w;

    que.push({sr,sc,0});
    visit[sr][sc] = true;

    COD now, next;

    while(que.size()){
        now = que.front(); que.pop();
        if(now.r == fr && now.c == fc) return!(cout << now.t);

        for(int d = 0; d < 4; d++){
            next.r = now.r;
            next.c = now.c;
            int ch = (d>>1) * h + ((d>>1)^1) * w;
            bool ok = true;
            for(int i = 0; i < ch; i++){
                int nr = next.r + dr[d]*gob[d];
                int nc = next.c + dc[d]*gob[d];

                if(nr < 0 || nr >= n || nc < 0 || nc >= m) {
                    ok = false; break;
                }
                if(arr[nr][nc] == 1) {ok = false; break;}
                next.r += ddr[d>>1];
                next.c += ddc[d>>1];
            }

            if(ok){
                next.r = now.r + dr[d], next.c = now.c + dc[d];
                next.t = now.t +1;
                if(visit[next.r][next.c]) continue;
                visit[next.r][next.c] =  true;

                que.push(next);
            }
        }
    }
    cout << -1;

    return 0;
}
