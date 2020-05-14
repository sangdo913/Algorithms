#include<vector>
#include<algorithm>

using namespace std;

vector<long long> temp;
int merge(vector<long long> &arr, int a, int b){
    int l = a, m = (a + b)/2, r = m+1, k = l;
    int ret = 0;
    while(l <= m && r <= b){
        if(arr[l] <= arr[r]){
            temp[k++] = arr[l++];
        }
        else{
            int idx = upper_bound(arr.begin() + a, arr.begin() + m+1, 2LL*arr[r]) - (arr.begin());
            ret += m+1 - idx;
            temp[k++] = arr[r++];
        }
    }
    while(l<=m){ temp[k++] =arr[l++]; }
    while(r<=b) {
            int idx = upper_bound(arr.begin() + a, arr.begin() + m+1, 2LL*arr[r]) - (arr.begin());
            ret += m+1 - idx;
        temp[k++] = arr[r++];
    }
    for(int i = a; i <= b; ++i) arr[i] = temp[i];
    return ret;
}

int mergesort(vector<long long>& arr, int a, int b){
    int ret = 0;
    if(a < b){
        int m = (a+b)/2;
        ret += mergesort(arr, a,m);
        ret += mergesort(arr, m+1,b);
        ret += merge(arr, a, b);
    }
    return ret;
}

class Solution {
public:
    int reversePairs(vector<int>& nums) {
        vector<long long> vec(nums.begin(), nums.end());
        temp.resize(nums.size());
        return mergesort(vec, 0, vec.size()-1);
    }
};