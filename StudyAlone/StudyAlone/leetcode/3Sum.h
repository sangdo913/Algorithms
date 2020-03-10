#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

class Solution {
public:
    vector<vector<int>> threeSum(vector<int>& nums) {
        if(nums.size() < 3) return vector<vector<int>>();
        sort(nums.begin(), nums.end());
        vector<int> vec;
        vector<int> num;
        vector<vector<int>> res;
        
        for(int i = 0; i < nums.size();){
            int j = i;
            ++i;
            int n = 1;
            while(i < nums.size() && nums[i] == nums[j]){
                ++n;
                ++i;
            }
            vec.push_back(nums[j]);
            num.push_back(n);
        }
        
        for(int i = 0; i < vec.size(); ++i){
            for(int j = i; j < vec.size(); ++j){
                int des = -(vec[i] + vec[j]);
                int k = lower_bound(vec.begin()+j, vec.end(), des) - vec.begin();
                if(j <= k && k < vec.size() && vec[k] == des){
                    num[i]--; num[j]--; num[k]--;
                    if(num[i] >=0 && num[j] >= 0 && num[k] >= 0){
                        res.push_back(vector<int>({vec[i],vec[j],vec[k]}));
                    }
                    num[i]++; num[j]++; num[k]++;
                }
            }
        }
        
        return res;
    }
};