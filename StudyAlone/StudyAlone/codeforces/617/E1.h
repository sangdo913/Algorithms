#include<iostream>

using namespace std;
int n;
char str[201];
char dp[256][200];

int main(){
    freopen("0Text.txt", "r", stdin);
    cin >> n >> str;
    dp[str[0]][0] = '0';

    bool cansort =true;
    for(int i = 1; i < n; ++i){
        char val = '0';
        for(int j = 'a'; j <= 'z'; ++j) dp[j][i] = dp[j][i-1];
        for(int j = 'z'; j > str[i]; --j){
            if(dp[j][i-1] == '1'){
                goto FAIL;
            }
            else if(dp[j][i-1] == '0'){
                val = '1';
            }
        }
        dp[str[i]][i] = val;
    }
    cout <<"YES\n";
    for(int i = 0; i < n; ++i) cout << dp[str[i]][i];
    return 0;
    FAIL:
    cout <<"NO\n";

    return 0;
}