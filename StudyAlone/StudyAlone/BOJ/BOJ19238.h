#include<iostream>
#include<queue>

using namespace std;
int remain;
int n, m; 
int tr, tc;
int mymap[20][20];
int dr[4] = {-1,1,0,0};
int dc[4] = {0,0,-1,1};
int sr[400], sc[400], desr[400], desc[400];
int visit[20][20];
int query;

int getdist(int r, int c){
    query++;
    int dist = 0;
    queue<int>q;
    visit[tr][tc] = query;
    q.push(tr*21+tc);
    while(!q.empty()){
        int cnt = q.size();
        while(cnt--){
            int now = q.front(); q.pop();
            int nr = now/21, nc = now%21;
            if(nr == r && nc == c) return dist;
            for(int d = 0; d < 4; ++d){
                int nnr = nr + dr[d], nnc = nc + dc[d];
                if(nnr < 0 || nnr == n || nnc < 0 || nnc == n) continue;
                if(visit[nnr][nnc] == query) continue;
                if(mymap[nnr][nnc] == 1) continue;
                visit[nnr][nnc] = query;
                q.push(nnr*21+nnc);
            }
        }
        dist++;
    }
    return 0x3f3f3f3f;
}

bool go(){
    query++;
    int dist = 0;
    queue<int> q;
    priority_queue<int> pq;
    visit[tr][tc] = query;
    q.push(tr*21+tc);

    while(!q.empty()){
        int r = q.size();

        while(r--){
            int now = q.front(); q.pop();
            int nr = now/21, nc = now%21;
            if(mymap[nr][nc] > 1){
                pq.push(-(nr*21+nc));
                continue;
            }
            for(int d = 0; d < 4; ++d){
                int nnr = nr+dr[d], nnc = nc+ dc[d];
                if(nnr < 0 || nnr == n || nnc < 0 || nnc == n) continue;
                if(visit[nnr][nnc] == query) continue;
                if(mymap[nnr][nnc] == 1) continue;
                visit[nnr][nnc] = query;
                q.push(nnr*21+nnc);
            }
        }
        if(!pq.empty()){
            int now = -pq.top();
            int nr = now/21 , nc = now%21;
            int id = mymap[nr][nc]-3;
            if(dist > remain) return false;
            remain-=dist;
            tr = nr, tc = nc;
            int need = getdist(desr[id], desc[id]);
            if(remain < need) return false;
            remain = remain + need;
            mymap[nr][nc] = 0;
            tr = desr[id];
            tc = desc[id];
            return true;
        }
        dist++;
    }
    return false;
}

int main(){
    freopen("0Text.txt", "r", stdin);
    cin >> n >> m >> remain;
    for(int i = 0; i < n; ++i) for(int j = 0; j < n; ++j) cin >> mymap[i][j];
    cin >> tr >> tc;
    tr--,tc--;
    for(int i = 0; i < m;++i){
        cin >> sr[i] >> sc[i] >> desr[i] >> desc[i];
        sr[i]--, sc[i]--, desr[i]--, desc[i]--;
        mymap[sr[i]][sc[i]] = 3 + i;
    }
    for(int i = 0; i < m; ++i){
        bool res = go();
        if(!res) {
            cout << -1 ;
            return 0;
        }
    }
    cout <<remain;
    return 0;
}