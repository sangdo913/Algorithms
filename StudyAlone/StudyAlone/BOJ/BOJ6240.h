#include<iostream>

using namespace std;

char str[2001];
int S[2001];
int n, m;
int dp[2000][2000];
int pi[27];
int pd[27];
int conv[256];

int getres(int s, int e){
    if(s >= e) return 0;
    int &ret = dp[s][e];
    if(ret != -1) return ret;
    ret = 0x3f3f3f3f;
    if(S[s] == S[e]){
        return ret = getres(s+1, e-1);
    }
    else{
        int res;
        if(S[s]) {
            res = pi[S[s]] + getres(s+1,e);
            if(res < ret) ret= res;
        }
        if(S[e]){
            res = pi[S[e]] + getres(s, e-1);
            if(res < ret) ret = res;
        }
    }
    return ret;
}

int main(){
    freopen("0Text.txt", "r", stdin);
    int n;
    cin >> n >> m;
    cin >> str;
    for(int i= 1; i <= n; ++i){
        char c;
        cin >> c;
        conv[c] = i;
        cin >> pi[i] >> pd[i];
        if(pi[i] > pd[i]) pi[i] = pd[i];
    }
    for(int i = 0; i < m; ++i) S[i] = conv[str[i]];
    for(int i = 0; i < m; ++i){
        for(int j = 0; j < m; ++j) dp[i][j] = -1;
    }
    
    return !(cout << getres(0,m-1));
}