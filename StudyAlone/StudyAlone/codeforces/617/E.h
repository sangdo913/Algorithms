#include<iostream>

using namespace std;

char s[200001];
int dp[26][200000];
int conv[256];
int n;

int main(){
    freopen("0Text.txt", "r", stdin);
    for(int i = 'a'; i <= 'z'; ++i) conv[i] = i-'a';
    cin >> n;
    cin >> s;

    dp[conv[s[0]]][0]= 1;
    int rmax = 1;
    for(int i = 1; i < n; ++i) {
        int mmax = 0;
        for(int j = 0;j < 26; ++j) dp[j][i] = dp[j][i-1];
        for(int j = conv['z']; j > conv[s[i]]; --j){
            if(mmax < dp[j][i-1]){
                mmax = dp[j][i-1];
            }
        }
        if(rmax < mmax+1) rmax = mmax+1;
        dp[conv[s[i]]][i] = mmax+1;
    }
    cout << rmax << endl;
    for(int i = 0; i < n; ++i) cout << dp[conv[s[i]]][i] << ' ';

    return 0;
}