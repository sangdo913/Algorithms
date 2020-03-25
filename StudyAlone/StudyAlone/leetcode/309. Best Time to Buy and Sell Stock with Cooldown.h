#include<iostream>
#include<vector>
using namespace std;

#define MAX(x,y) ((x) > (y) ? (x) :(y))
#define BUY 0
#define SELL 1

class Solution {
public:
    int maxProfit(vector<int>& prices) {
        if(prices.size() < 2) return 0;
        int n = prices.size();
        vector<vector<int>> dp(2, vector<int>(n,0));
        dp[BUY][0] = -prices[0];
        
        for(int i = 1; i < n; ++i){
            int res = dp[BUY][i-1] + prices[i];
            dp[SELL][i] = MAX(dp[SELL][i-1],res);
            res = i != 1 ? dp[SELL][i-2] - prices[i] : -prices[i];
            dp[BUY][i] = MAX(dp[BUY][i-1], res);
        }
        
        return dp[SELL][n-1];
    }
};