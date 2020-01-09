#include<iostream>
#include<vector>

using namespace std;

struct Bucket {
    bool isin;
    int min, max;
};
class Solution {
public:
    int maximumGap(vector<int> nums) {
        if (nums.size() == 1) return 0;
        vector<Bucket> buckets;
        int mmax = -1;
        int mmin = 0x7fffffff;
        for (int i = 0; i < nums.size(); ++i) {
            mmax = mmax < nums[i] ? nums[i] : mmax;
            mmin = mmin < nums[i] ? mmin : nums[i];
        }
        int diff = mmax - mmin;
        int range = diff / (nums.size()+1)+1;
        
        buckets.resize(nums.size()+1);
        for (int i = 0; i < buckets.size(); ++i) {
            buckets[i].isin = false;
            buckets[i].max = -1;
            buckets[i].min = 0x7fffffff;
        }
        for (int i = 0; i < nums.size(); ++i) {
            int idx = (nums[i]-mmin) / range;
            buckets[idx].isin = true;
            if (buckets[idx].max < nums[i]) buckets[idx].max = nums[i];
            if (buckets[idx].min > nums[i]) buckets[idx].min = nums[i];
        }
        int prev = 0;
        while (!buckets[prev].isin) prev++;
        int res = -1;
        for (int i = prev + 1; i < nums.size() + 1; ++i) {
            int jump = 0;
            while (i <= nums.size() && !buckets[i].isin) ++i;
            if (i <= nums.size()) {
                int num = buckets[i].min - buckets[prev].max;
                res = res < num ? num : res;
            }
            prev = i;
        }
        return res;
    }
};