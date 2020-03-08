#include<iostream>
#include<cstring>

using namespace std;

int dr[2] = {1,1};
int dc[2] = {-1,1};
char mymap[8][9];
char mycheck[2][8][9];
int adj[64][8];
int alen[64];
int gnum[2];
int n;
int asel[64];
int bselected[64];
int visit[64];
int tc;
bool dfs(int a) {
    if(visit[a] == tc) return false;
    visit[a] = tc;
    for(int i = 0; i < alen[a]; ++i){
        int b = adj[a][i];
        if(bselected[b] == -1 || dfs(bselected[b])){
            bselected[b] = a;
            return true;
        }
    }
    return false;
}

int main(){
    freopen("0Text.txt", "r" ,stdin);
    int C;
    cin >> C;
    while(C--){
        memset(mycheck, 0 ,sizeof(mycheck));
        memset(alen,0,sizeof(alen));
        int n;
        cin >> n;
        for(int i = 0; i < n; ++i){
            cin >> mymap[i];
        }
        gnum[0] = gnum[1] = 0;
        for(int i = 0; i < n; ++i){
            for(int j = 0; j < n; ++j){
                if(mymap[i][j] == '*') continue;
                for(int d = 0; d < 2; ++d){
                    if(mycheck[d][i][j]) continue;
                    gnum[d]++;
                    int nr = i, nc = j;
                    while(nr >= 0 && nc >= 0 && nr < n && nc < n){
                        if(mymap[nr][nc] == '*') break;
                        mycheck[d][nr][nc] = gnum[d];
                        nr += dr[d], nc += dc[d];
                    }
                }
            }
        }
        for(int i = 0; i < n; ++i){
            for(int j = 0; j < n; ++j){
                if(mymap[i][j] == '.'){
                    int g1 = mycheck[0][i][j];
                    int g2 = mycheck[1][i][j];
                    adj[g1][alen[g1]++] = g2;
                }
            }
        }
        int res = 0;
        // for(int d = 0; d < 2; ++d){

        // for(int i = 0; i < n; ++i){
        //      for(int j = 0; j < n; ++j) cout << (int)(mycheck[d][i][j]) << ' ';
        //      cout << '\n';
        // }
        // cout << '\n';
        // }
        // cout <<'\n';
        memset(bselected, -1, sizeof(bselected));
        for(int i = 1; i <= gnum[0]; ++ i){
            tc++;
            res += dfs(i);
        }
        cout << res << '\n';
    }
    return 0;
}