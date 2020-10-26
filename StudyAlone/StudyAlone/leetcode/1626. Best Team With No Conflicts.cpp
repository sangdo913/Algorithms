#include<vector>
#include<algorithm>
using namespace std;

int dp[1000];

class Solution {
public:
    int bestTeamScore(vector<int>& scores, vector<int>& ages) {
        int n = scores.size();
        vector<pair<int,int>> v(n);
        for(int i = 0; i < n; ++i){
            v[i] = {scores[i], ages[i]};
        }
        sort(v.begin(), v.end());
        
        dp[0] = v[0].first;
        int res = 0;
        for(int i = 0; i < n; ++i){
            dp[i] = v[i].first;
            for(int j = 0; j < i; ++j){
                if(v[i].second < v[j].second && v[i].first > v[j].first) continue;
                dp[i] = max(dp[i], dp[j] + v[i].first);
            }
            res = max(res, dp[i]);
        }
        
        return res;
    }
};