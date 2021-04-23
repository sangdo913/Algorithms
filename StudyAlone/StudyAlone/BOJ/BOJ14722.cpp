#include<iostream>
#include<cstring>

using namespace std;

int dp[3][1000][1000];
int mymap[1000][1000];

int n;
int dr[2] = {0,1};
int dc[2] = {1,0};

int dfs(int i, int j, int t) {
    if(i ==n || j == n) return 0;
    if(i == n-1 && j == n-1){
        dp[t][i][j] = mymap[i][j] == t;
        return dp[t][i][j];
    }
    if(dp[t][i][j] != -0x3f3f3f3f){
        return dp[t][i][j];
    }
    dp[t][i][j] = 0;
    if(mymap[i][j] == t){
        dp[t][i][j] = max(dp[t][i][j] ,max(dfs(i+1,j,(t+1)%3), dfs(i,j+1,(t+1)%3))+1);
    }
    return dp[t][i][j] = max(dp[t][i][j], max(dfs(i+1,j,t), dfs(i,j+1,t)));
}

int getdp(){
    for(int i = 0; i < n;++i) {
        for(int j = 0; j < n; ++j) {
            if(mymap[i][j] == 0){
                dp[0][i][j] = max(1, dp[0][i][j]);
            }
            for(int k = 0;k < 3;++k) {
                for(int d = 0; d < 2; ++d) {
                    int ni = i + dr[d];
                    int nj = j + dc[d];
                    if(ni == n || nj == n) continue;
                    if((k+1)%3 == mymap[ni][nj]) {
                        dp[(k+1)%3][ni][nj] = max(dp[k][i][j] + 1,dp[(k+1)%3][ni][nj]);
                    }
                    else dp[k][ni][nj] = max(dp[k][i][j], dp[k][ni][nj]);
                }
            }
        }
    }
    int res =0;

    for(int d = 0; d < 3; ++d) res= max(res, dp[d][n-1][n-1]);
    return res;
}

int main() {
    freopen("0Text.txt", "r", stdin);
    cin >> n;
    for(int i = 0; i < n; ++i){
        for(int j = 0; j < n ;++j){
            cin >> mymap[i][j];
        }
    }
    for(int i = 0; i < n; ++i){
        for(int j = 0; j < n; ++j){
            for(int d = 0; d < 3; ++d) dp[d][i][j] = -0x3f3f3f3f;
        }
    }
    cout << getdp() << endl;

    return 0;
}