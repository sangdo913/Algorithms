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

/*
class Solution {
public:
    int bestTeamScore(vector<int>& scores, vector<int>& ages) {
        vector<pair<int,int>> v;
        int n = scores.size();
        for(int i = 0; i < n; ++i){
            v.push_back({ages[i], scores[i]});
        }
        sort(v.begin(), v.end());
        map<int,int> mp;
        mp[0] = 0;
        for(int i = 0; i < n; ++i){
            auto[_,s] = v[i]; 
            auto it = mp.upper_bound(s);
            auto cur= prev(it);
            int sum = cur->second + s;
            while(it != mp.end() && it->second <= sum){
                it = mp.erase(it);
            }
            mp[s] = cur->second + s;
        }
        int res = 0;
        for(auto it : mp){
            res = max(res,it.second);
        }
        return res;
    }
};
*/