#include<iostream>
#include<vector>

using namespace std;

class Solution {
public:
    int lower(int a, vector<int> &v2){
        int s =0, e = v2.size()-1, m;
        while(s<=e){
            m = (s+e)/2;
            if(v2[m] < a){ s = m+1;}
            else e = m-1;
        }
        return s;
    }
    int upper(int a, vector<int> &v){
        int s = 0, e = v.size()-1, m;
        while(s<=e){
            m = (s+e)/2;
            if(v[m] <= a) s = m+1;
            else e = m-1;
        }
        return s;
    }

    int bs(int idx, vector<int>& v1, vector<int>& v2){
        int s = 0, e = v1.size()-1, m;
        while(s<=e){
            m = (s+e)/2;
            int i = lower(v1[m], v2);
            if(i + m< idx) s = m+1;
            else if(i+m > idx) e = m-1;
            else return v1[m];
        }
        s = 0, e = v2.size()-1;
        while(s<=e){
            m = (s+e)/2;
            int i = upper(v2[m], v1);
            if(i+m < idx) s = m + 1;
            else if(i + m > idx) e= m-1;
            else return v2[m];
        }
        return -1;
    }
    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
        int n = nums1.size() + nums2.size();
        if(n&1) return (double) bs(n/2,nums1, nums2);
        else return ((double)bs((n-1)/2, nums1, nums2) + bs((n-1)/2+1, nums1, nums2))/2.0;
    }
};

int main(){
    freopen("0Text.txt", "r" ,stdin);
    int n, m;
    vector<int> v1, v2;
    scanf("%d %d", &n,&m);
    v1.resize(n), v2.resize(m);
    for(int i = 0; i < n; ++i) scanf("%d", &v1[i]);
    for(int j = 0; j < m; ++j) scanf("%d" , &v2[j]);
    cout << Solution().findMedianSortedArrays(v1, v2);
    return 0;
}