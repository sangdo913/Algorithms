#include<iostream>
#include<cstring>

using namespace std;

int arr[500][500];
int n,m;
int trace[2][500][500];
int dp[2][500][500];
int balnum[500][500];

int dr[8] = {-1,-1,-1,0,0,1,1,1};
int dc[8] = {-1,0,1,-1,1,-1,0,1};

int Do(){
    cin >> n>> m;
    ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    
    memset(trace, -1, sizeof(trace));
    memset(dp, -1, sizeof(dp));

    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++) cin >> arr[i][j];
    }

    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            int nr = i, nc = j;
            int num = arr[i][j];

            while(dp[0][nr][nc] == -1){
                int r = -1, c = -1;
                for(int d = 0; d < 8; d++){
                    int tr = nr + dr[d], tc = nc + dc[d];
                    if(0 <= tr && tr < n && 0 <= tc && tc  < m){
                        if(num > arr[tr][tc]){
                            r = tr, c = tc;
                            num = arr[tr][tc];
                        }
                    }
                }

                if(r == -1) {
                    dp[0][nr][nc] = nr, dp[1][nr][nc] = nc;
                    break; 
                }
                else{
                    trace[0][r][c] = nr, trace[1][r][c] = nc;
                    nr = r, nc = c;
                }
            }

            int sr = dp[0][nr][nc], sc = dp[1][nr][nc], nnr, nnc;
            while(nr != -1){
                dp[0][nr][nc] = sr, dp[1][nr][nc] = sc;
                nnr = trace[0][nr][nc], nnc = trace[1][nr][nc] ;
                nr = nnr, nc  = nnc;
            }

            balnum[dp[0][i][j]][dp[1][i][j]]++;
        }

    }


    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            cout << balnum[i][j] << ' ';
        }
        cout << '\n';
    }
    return 0;
}