#include<iostream>
#include<vector>
#include<queue>
#include<algorithm>

using namespace std;

#define ull unsigned long long
class Solution {
public:
    int maxPerformance(int n, vector<int>& speed, vector<int>& efficiency, int k) {
        ull res = 0, allnum = 0;
        vector<pair<int,int>> infos(n);
        for(int i = 0; i < n; ++i) infos[i] = {efficiency[i], speed[i]};
        sort(infos.begin(), infos.end());
        priority_queue<ull> pq;
        for(int i = n-1; i >= 0; --i){
            pq.push(-infos[i].second);
            allnum += infos[i].second;
            if(pq.size() > k){
                allnum+=pq.top(); pq.pop();
            }
            ull v = allnum * infos[i].first;
            res = max(res,v); 
        }
        return res%1000000007;
    }
};