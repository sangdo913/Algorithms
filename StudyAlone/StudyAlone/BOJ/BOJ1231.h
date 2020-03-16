#include<iostream>

using namespace std;

int dp[51][500001];
int jusic[51][10];

int main(){
    freopen("0Text.txt", "r", stdin);
    int c, d, m;
    scanf("%d %d %d", &c, &d, &m);
    
    for(int i = 1; i <= c; ++i){
        for(int j = 0; j < d; ++j) 
        scanf("%d", &jusic[i][j]);
    }
    
    for(int k = 0; k < d-1; ++k){
        for(int i = 1; i <=m; ++i) dp[k][i] = i;
            for(int j = 1; j <= c; ++j){
                for(int i = jusic[j][k]; i <= m; ++i){
                    if(dp[k][i] < dp[k][i-jusic[j][k]] + jusic[j][k+1])
                        dp[k][i] = dp[k][i-jusic[j][k]] + jusic[j][k+1];
                }
            }
        m = dp[k][m];
    }
    cout << m;

    return 0;
}