#include<vector>
using namespace std;

#define MAX(x, y) ((x) > (y) ? (x) : (y))
int n, m;
vector<vector<int>> dp;
vector<vector<int>> *arr;
int dr[4] = {-1,1,0,0};
int dc[4] = {0,0,-1,1};

int getres(int i, int j){
    int &ret = dp[i][j];
    if(ret != -1) return dp[i][j];
    ret = 1;
    
    for(int d = 0; d < 4; ++d){
        int ni = dr[d] + i;
        int nj = dc[d] + j;
        if(ni < 0 || n <= ni || nj < 0 || m <= nj) continue;
        if((*arr)[ni][nj] < (*arr)[i][j]) {
            int res = getres(ni,nj) + 1;
            if(res > ret) ret = res;
        }
    }
    return ret;
}

class Solution {
public:
    int longestIncreasingPath(vector<vector<int>>& matrix) {
        if(!matrix.size()) return 0;
        arr = &matrix;
        n = matrix.size();
        m = matrix[0].size();
        dp = vector<vector<int>>(n,vector<int>(m, -1));
        int res = 1;
        
        for(int i = 0; i < n; ++i){
            for(int j = 0; j < m; ++j){
                int r = getres(i,j);
                if(res < r) res= r;
            }
        }
        
        return res;
    }
};