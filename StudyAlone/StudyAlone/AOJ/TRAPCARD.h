#include<iostream>
#include<cstring>

using namespace std;
char mymap[20][21];
struct POS{
    int r,c;
};
POS Q[1000];
int dr[4] = {-1,1,0,0};
int dc[4] = {0,0,-1,1};
int tc;
int visit[20][20];
int h,w;
int adj[400][4];
int alen[400];
int gA[400];
int gB[400];
int myselect[400];
int selected[400];
int bvisit[400];
int selectbackup[400];
int tc2;
int G[400];
int Q1[400];
int Q2[400];
int mycheck1[20][20];
int mycheck2[20][20];

bool mymatch(int a){
    if(bvisit[a] == tc2) return false;
    bvisit[a] = tc2;
    for(int i = 0; i < alen[a]; ++i){
        int b = adj[a][i];
        if(selected[b] == -1 || mymatch(selected[b])){
            selected[b] = a;
            myselect[a] = b;
            return true;
        }
    }
    return false;
}

int maketrap(int re){
    int asize = 0, bsize = 0;
    for(int i = 0; i < re; ++i){
        int r = Q[i].r, c = Q[i].c;

        int id = r*w + c;
        alen[id] = 0;
        if(G[id] %2) gA[asize++] = id;
        else gB[bsize++] = id;

        for(int d = 0; d < 4; ++d){
            int nr = r + dr[d], nc = c + dc[d];
            if(0<=nr && nr < h && 0<=nc && nc < w && mymap[nr][nc] == '.') 
            adj[id][alen[id]++] = nr*w + nc; 
        }
    }

    memset(myselect, -1, sizeof(myselect));
    memset(selected, -1, sizeof(selected));
    int a1 = 0;
    int f =0, r = 0;
    for(int i = 0; i < asize; ++i){
        tc2++;
        bool matched = mymatch(gA[i]);
        a1+=matched;
    }
    for(int i = 0; i < re; ++i){
        int tid = Q[i].r*w + Q[i].c;
        if(selected[tid] == -1 && myselect[tid] == -1){
            Q1[r++] = tid;
            mycheck1[Q[i].r][Q[i].c] = tc;
        }
    }
    if(r == 0){
        Q1[r++] = Q[0].r*w + Q[0].c;
        mycheck1[Q[0].r][Q[0].c] = tc;
    }
    int ret = 0;

    while(r != f){
        int nr = Q1[f]/w;
        int nc = Q1[f++]%w;
        bool istrap = true;

        for(int d = 0; d < 4 ;++d){
            int nnr = nr + dr[d];
            int nnc = nc + dc[d];
            if(0<=nnr && nnr < h && 0 <= nnc && nnc < w){
                if(mymap[nnr][nnc] == '^'){
                    istrap = false;
                }
                if(mycheck1[nnr][nnc] ==tc)continue;
                if(mymap[nnr][nnc] == '#') continue;
                mycheck1[nnr][nnc] = tc;
                Q1[r++] = nnr*w + nnc;
            }
        }
        if(istrap) {
            mymap[nr][nc] = '^';
            ret++;
        }
    }

    return ret;
}

int findmap(int r, int c){
    int fr = 0, re = 0;
    visit[r][c] = tc;
    Q[re].r = r;
    Q[re++].c = c;

    while(fr != re){
        int nr = Q[fr].r;
        int nc = Q[fr++].c;
        for(int d= 0; d < 4; ++d){
            int nnr = nr+dr[d], nnc = nc + dc[d];
            if(0<=nnr && nnr < h && 0 <= nnc && nnc < w){
                if(visit[nnr][nnc] == tc) continue;
                visit[nnr][nnc] = tc;
                if(mymap[nnr][nnc] == '.'){
                    Q[re].r = nnr;
                    Q[re++].c = nnc;
                }
            }
        }
    }
    return maketrap(re);
}

int main(){
    freopen("0Text.txt", "r", stdin);
    int C;
    cin >> C;
    while(C--){
        tc++;
        cin >> h >> w;
        for(int i = 0; i < h; ++i) cin >> mymap[i];
        int cnt = 0;
        for(int i = 0; i < h; ++i){
            cnt = i%2;
            for(int j = 0; j < w; ++j){
                G[i*w+j] = cnt;
                cnt^=1;
            }
        }
        int res = 0;
        for(int i = 0; i < h; ++i){
            for(int j = 0; j < w; ++j){
                if(mymap[i][j] == '.' && visit[i][j] != tc){
                    res += findmap(i,j);
                }
            }
        }
        cout << res << '\n';
        for(int i = 0; i < h; ++i){
            cout << mymap[i] << '\n';
        }
    }
    return 0;
}