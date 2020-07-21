//https://leetcode.com/problems/palindrome-partitioning-ii/
#include<iostream>
#include<vector>
#include<string>

using namespace std;

string str;
vector<vector<int>> ispelin;
vector<int> dp;
int getdp(int i){
    if(ispelin[i][str.size()-1]) return 0;
    if(dp[i] != -1){
        return dp[i];
    }
    dp[i] = 0x3f3f3f3f;
    for(int idx = i; idx < str.size(); ++idx){
        if(ispelin[i][idx]){
            dp[i] = min(dp[i], 1 + getdp(idx+1));
        }
    }
    return dp[i];
}

class Solution {
public:
    int minCut(string s) {
        str = s;
        int n = s.size();
        dp = vector<int>(n,-1);
        ispelin = vector<vector<int>>(n, vector<int>(n,1));
        
        for(int i = 1; i < n; ++i){
            int ii = 0, jj = i;
            for(int cnt = n-i; cnt; --cnt, ++ii, ++jj){
                if(s[ii] != s[jj] || (ii+1 < jj-1 && !ispelin[ii+1][jj-1])) {
                  ispelin[ii][jj] = 0;  
                } 
            }
        }
        
        return getdp(0);
    }
};