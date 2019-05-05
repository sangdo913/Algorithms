#include<iostream>
#include<cstring>

using namespace std;

const int MOD = 1000000009;
int dp[4][50001]; // 0 : 1Ä­ , 1 : 2Ä­(Àü¿¡ 1Ä­), 2 : -1Ä­, 3 : 2Ä­(Àü¿¡ -1Ä­)
int n;

int dfs(int now, int p, int pp){
    int idx = p;
    if(p == 1 && pp == 2) idx = 3;
    int &ret = dp[idx][now];
    
    if(ret!= -1 ) return ret;

    if(now == n && p == 0) return ret = 1;
    else if(now == n && p == 1 && pp == 2) return ret = 1;
    else if(now == n && p == 1 && pp == 0) return ret = 1;
    else if(now >= n) return ret= 0;
    
    ret = 0;
    if(p == 0){
        ret += dfs(now+1, 0, p);
        ret %=MOD;
        ret += dfs(now+2, 1,p);
        ret %=MOD;
    }
    else if(p == 1){
        if(pp == 0){
            ret += dfs(now-1, 2, p);
            ret %=MOD;
        }
        else if(pp == 2){
            ret += dfs(now + 1, 0, p);
            ret %=MOD;
            ret += dfs(now+ 2, 1, p);
            ret %=MOD;
        }
    }
    else{
        ret += dfs(now+2, 1, p);
        ret %=MOD;
    }
    return ret;
}

int Do(){
    memset(dp,-1,sizeof(dp));
    cin >> n;
    cout << dfs(1,0,0);

    return 0;
}