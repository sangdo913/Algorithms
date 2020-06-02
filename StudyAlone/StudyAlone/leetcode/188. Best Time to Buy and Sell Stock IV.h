#include<iostream>
#include<vector>
using namespace std;

class Solution {
public:
    int maxProfit(int k, vector<int>& prices) {
        vector<int> sell;
        vector<int> buy;
        int n = prices.size();
        int res = 0;
        if(k>=n/2){
            for(int i = 1; i < n; ++i){
                if(prices[i] > prices[i-1]) res += prices[i] - prices[i-1];
            }
            return res;
        }
        sell.clear();
        buy.clear();
        sell.resize(k+1);
        buy.resize(k+1, -0x3f3f3f3f);
        for(int i = 0 ; i < n; ++i){
            for(int j = k; j ; --j){
                buy[j] = max(buy[j], sell[j-1] - prices[i]);
                sell[j] = max(buy[j] + prices[i] , sell[j]);
            }
        }
        return sell[k];
    }
};