#include<iostream>
#include<algorithm>
#include<vector>

using namespace std;

class Solution {
public:
    int maxProfit(vector<int>& prices) {
    int n = prices.size();
    int buy1 = -0x3f3f3f3f, sell1 = 0, buy2 = -0x3f3f3f3f, sell2 = 0;
    for(int i = 0; i < n; ++i){
        sell2 = max(sell2, buy2+prices[i]);
        buy2 = max(buy2, sell1 - prices[i]);
        sell1 = max(sell1, buy1 + prices[i]);
        buy1 = max(buy1, -prices[i]);
    }
     return max(sell1, sell2);   
    }
};