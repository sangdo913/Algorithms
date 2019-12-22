#include<iostream>

using namespace std;
struct MAL{
    int r, c;
    int mals[12];
    int mlen;
}mals[50000];

int n, k;
int mymap[14][14];
int dr[5] = {0,0,0,-1,1};
int dc[5] = {0,1,-1,0,0};
int info[14][14];
int pos[11];
int dir[11];
int mid = 1;
int main(){
    freopen("0Text.txt", "r", stdin);
    cin >> n >> k;
    for(int i = 0; i <= n+1; ++i){
        mymap[0][i] = 2;
        mymap[i][0] = 2;
        mymap[n+1][i] = 2;
        mymap[i][n+1] = 2;
    }
    for(int i = 1; i <= n; ++i) for(int j = 1; j <= n; ++j) cin >> mymap[i][j];
    for(int i = 1; i <= k; ++i) {
        MAL &m = mals[mid];
        cin >> mals[i].r >> mals[i].c >> dir[i];
        mals[i].mlen = 1;
        mals[i].mals[0] = i;
        pos[i] = i;
        info[mals[i].r][mals[i].c]= i;
        mid++;
    }
    for(int t = 1; t <= 1000; ++t){
        for(int i = 1; i <= k; ++i){
            MAL&m = mals[pos[i]];
            int r = m.r;
            int c = m.c;
            int nr = r+ dr[dir[i]];
            int nc = c + dc[dir[i]];

            if(mymap[nr][nc] == 2) {
                dir[i] = ((dir[i]-1)^1) + 1;
                nr = r + dr[dir[i]];
                nc = c + dc[dir[i]];
                if(mymap[nr][nc] == 2) continue; 
            }

            int k;
            for(k = 0; k < m.mlen; ++k) if(m.mals[k] == i) break;
            int remain = k;
            if(mymap[nr][nc] == 1){
                int len = m.mlen - k;
                for(int j = 0; j < len/2; ++j){
                    int temp = m.mals[k + j];
                    m.mals[j+k] = m.mals[m.mlen-1-j];
                    m.mals[m.mlen-1-j] = temp;
                }
            }
            if(info[nr][nc]){
                MAL& nm = mals[info[nr][nc]];
                for(int j = k; j < m.mlen; ++j) {
                    pos[m.mals[j]] = info[nr][nc];
                    nm.mals[nm.mlen++] = m.mals[j];
                }
                m.mlen = remain;
                if(!remain) info[m.r][m.c] = 0;
            }
            else{
                MAL& nm = mals[mid];
                nm.r = nr, nm.c = nc;
                int j = k;
                for(;j < m.mlen; ++j){
                    pos[m.mals[j]] = mid;
                    nm.mals[nm.mlen++] = m.mals[j];
                }
                m.mlen = remain;
                if(remain == 0) info[m.r][m.c] = 0;
                mid++;
            }
            if(mals[pos[i]].mlen >= 4) return !(cout << t);
            info[mals[pos[i]].r][mals[pos[i]].c] = pos[i];
        }
    }

    return !(cout << -1);
}