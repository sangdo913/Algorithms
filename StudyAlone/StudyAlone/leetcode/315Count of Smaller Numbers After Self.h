#include<vector>
#include<iostream>
using namespace std;
vector<int> res;
vector<int> temp;
vector<int> idxes;
vector<int> *n;

void merge(int s, int e){
    int l = s, m = (s+e)/2,r = m+1, k = l;
    while(l <= m && r <= e) {
        if((*n)[idxes[l]] <= (*n)[idxes[r]]){
               res[idxes[l]] += r-m-1;
               temp[k++] = idxes[l++];
        }
        else{
            temp[k++] = idxes[r++];
        }
    }
    while(l <= m) {
        res[idxes[l]] += r-m-1;
        temp[k++] = idxes[l++];
    }
    while(r <= e) temp[k++] = idxes[r++];
    for(int i = s; i <= e; ++i) idxes[i] = temp[i];
}

void mergesort(int s, int e){
    if(s<e){
        int m = (s+e)/2;
        mergesort(s, m);
        mergesort(m+1,e);
        merge(s,e);
    }
}


class Solution {
public:
    vector<int> countSmaller(vector<int>& nums) {
        n = &nums;
        res.resize(nums.size());
        temp.resize(nums.size());
        idxes.resize(nums.size());
        for(int i = 0; i < nums.size(); ++i) 
            idxes[i] = i, res[i] = 0;
        
        mergesort(0,nums.size()-1);
        return res;
    }
};