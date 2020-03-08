//https://leetcode.com/problems/first-missing-positive/
///Runtime: 0 ms, faster than 100.00% of C++ online submissions for First Missing Positive.
//Memory Usage: 8.8 MB, less than 44.00% of C++ online submissions for First Missing Positive.
#include<vector>
using namespace std;

class Solution {
public:
    int firstMissingPositive(vector<int>& nums) {
        for(int i = 0; i < nums.size(); ++i){
            while((0<nums[i] && nums[i] != i+1)){
                if(nums.size() < nums[i]) break;
                
                int to = nums[i] - 1;
                if(nums[to] == to+1){
                    break;
                }   
                int temp = nums[to];
                nums[to] = nums[i];
                nums[i] = temp;
            }
        }
        for(int i = 0; i < nums.size(); ++i) if(nums[i] != i + 1) return i+1;
        return nums.size()+1;
    }
};