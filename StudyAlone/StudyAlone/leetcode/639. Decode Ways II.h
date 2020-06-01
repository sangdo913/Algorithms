#include<iostream>
#include<string>
#include<vector>
using namespace std;

#define MOD 1000000007
string str;
vector<int> dp;
int ncnt[11*11];
int conv[256];

int getdp(int i){
    if(i == str.size()) return 1;
    if(dp[i] != -1) {
        return dp[i];
    }
    dp[i] = 0;
    
    //한자리
    if(str[i] == '0') return dp[i] = 0;
    else if(str[i] == '*') dp[i] = (1LL*getdp(i+1)*9)%MOD;
    else dp[i] = getdp(i+1);
    
    //두자리
    if(i +1 < str.size()){
        int c = conv[str[i]]*11 + conv[str[i+1]];
        dp[i] = (dp[i] + 1LL*ncnt[c]*getdp(i+2))%MOD;
    }
    
    return dp[i];
}

int getnum(int n[2]){
    if(n[0] == 0) return 0;
    else if(n[0] != 10 && n[0] > 2) return 0;
    else if(n[0] ==2 && n[1] != 10 && n[1] > 6) return 0;
    else if(n[0] == n[1]  && n[0] == 10) return 15;
    else if(n[0] == 10) {
        if(n[1] <= 6) return 2;
    }  
    else if(n[1] == 10){
        if(n[0] == 2) return 6;
        else return 9;
    }
    return 1; 
}
class Solution {
public:
    int numDecodings(string s) {
        int cnt = 1;
        for(int i = '0'; i <= '9'; ++i) conv[i] = i-'0';
        conv['*'] = 10;
        for(int i = 0; i <= 10; ++i) for(int j = 0; j <= 10; ++j){
            int n[2] = {i,j};
            ncnt[i*11+j] = getnum(n);
        }
        str = s;
        dp.clear();
        dp.resize(s.size(), -1);
        return getdp(0);
    }
};