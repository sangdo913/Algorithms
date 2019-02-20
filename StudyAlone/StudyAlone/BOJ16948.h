#include<iostream>
#include<cstring>

using namespace std;

int dr[6] = {-2, -2, 0,0,2,2};
int dc[6] = {-1,1,-2,2,-1,1};

int que[40000][2], n;
int dist[200][200];
int st[2], ed[2];

int Do(){
    cin >> n;
    cin >> st[0] >> st[1] >> ed[0] >> ed[1];

    memset(dist, -1, sizeof(dist));

    int fr = 0, re = 0;
    que[re][0] = st[0];
    que[re++][1] = st[1];
    dist[st[0]][st[1]] = 0;

    while(fr != re){
        int now[2] = {que[fr][0], que[fr++][1]};

        for(int d = 0; d < 6; d++){
            int next[2] = {now[0] + dr[d], now[1] + dc[d]};

            if(0 <= next[0] && next[0] < n && 0 <= next[1] && next[1] < n){
                if(dist[next[0]][next[1]] != -1) continue;
                dist[next[0]][next[1]] = dist[now[0]][now[1]] + 1;
                
                que[re][0] = next[0]; que[re++][1] = next[1];
            }
        }
    }

    cout << dist[ed[0]][ed[1]] ;
    return 0;
}