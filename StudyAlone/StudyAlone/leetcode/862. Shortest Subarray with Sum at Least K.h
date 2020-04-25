#include<vector>
using namespace std;
long long sum[50001];
int dq[50001];

class Solution {
public:
    int shortestSubarray(vector<int>& A, int K) {
        int n = A.size()+1;
        for(int i = 1; i <= A.size(); ++i){
            sum[i] = sum[i-1] + A[i-1];
        }
        int ans = 0x3f3f3f3f;
        int f = 0, r = 0;
        
        for(int i = 0; i < n; ++i){
            while(f != r && sum[i] <= sum[dq[r-1]]) r--;
            while(f != r && sum[i] - sum[dq[f]] >= K){
                if(ans > i-dq[f]){
                    ans = i-dq[f];
                }
                ++f;
            }
            dq[r++] = i;
        }
        
        return ans == 0x3f3f3f3f? -1 : ans;
    }
};