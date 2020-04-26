#include<iostream>

using namespace std;
int n;
int dp[11];
int muldp[11][11];

int dfs(int i, int j){
    if(j == 3){
        return dp[n] / dp[i-1];
    }
    int ret = 0;
    for(int k = i; k <= n-(3 - j); ++k){
        int temp = dp[k] / dp[i-1] + dfs(k+1, j+1); 
        if(ret < temp) ret = temp;
    }
    return ret;
}

int main(){
    freopen("0Text.txt", "r", stdin);
    int arr[10];

    cin >> n;
    dp[0] = 1;
    for(int i = 1; i <= n; ++i){
        int a;
        cin >> a;
        dp[i] = dp[i-1]*a;
    }
    cout << dfs(1, 0);
    
    return 0;
}