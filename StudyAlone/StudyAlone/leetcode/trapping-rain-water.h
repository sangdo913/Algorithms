#include<vector>
#include<iostream>
using namespace std;

#define MIN(x,y) ((x) > (y) ? (y) : (x))
#define MAX(x,y) ((x) > (y) ? (x) : (y))

class Solution {
public:
    int trap(vector<int>& height) {
        if(height.size() == 0) return 0;
        vector<int> water(height.size());
        int h = height[0];
        for(int i = 0; i < height.size(); ++i){
            if(h < height[i]){
               h = height[i];
            }
            water[i] = h;
        }
        h = height[height.size()-1];
        int res = 0;
        for(int i = height.size()-1; i >= 0; --i){
            if(h < height[i]){
                h = height[i];
            }
            water[i] = MIN(water[i], h);
            res += water[i] - height[i];
        }
        return res;
    }
};