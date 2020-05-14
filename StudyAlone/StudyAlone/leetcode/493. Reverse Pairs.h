#include<vector>
#include<algorithm>

using namespace std;

#define mytype int
vector<mytype> temp;
int merge(vector<mytype> &arr, int a, int b){
    int l = a, m = (a + b)/2, r = m+1, k = l;
    int ret = 0;
    int cursor = l;
    while(l <= m && r <= b){
        if(arr[l] <= arr[r]){
            temp[k++] = arr[l++];
        }
        else{
            while(cursor < m + 1 && arr[cursor] <= 2LL*arr[r]) cursor++;
            ret += m+1 - cursor;
            temp[k++] = arr[r++];
        }
    }
    while(l<=m){ temp[k++] =arr[l++]; }
    while(r<=b) {
        while(cursor < m+1 && arr[cursor] <= 2LL*arr[r]) cursor++;
        ret += m+1 -cursor;
        temp[k++] = arr[r++];
    }
    for(int i = a; i <= b; ++i) arr[i] = temp[i];
    return ret;
}

int mergesort(vector<mytype>& arr, int a, int b){
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
        temp.resize(nums.size());
        return mergesort(nums, 0, nums.size()-1);
    }
};