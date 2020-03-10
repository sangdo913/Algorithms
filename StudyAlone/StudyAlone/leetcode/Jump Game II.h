#include<iostream>
#include<vector>
using namespace std;

int dp[100000];
class Solution {
public:
    int jump(vector<int>& nums) {
        if(nums.size() == 1) return 0;
        int minid = 1;
        
        for(int i = 0; i < nums.size(); ++i){
            int next = i + nums[i];
            if(next >= nums.size()-1) return dp[i] + 1;
            
            for(int j = minid; j <=next; ++j){
                dp[j] = dp[i] + 1;
            }
            
            if(next + 1 > minid) minid = next+1;
        }
        return -1;
    }
};