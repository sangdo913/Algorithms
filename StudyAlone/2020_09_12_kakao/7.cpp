#include <string>
#include<iostream>
#include <vector>
#include<algorithm>

using namespace std;
vector<long long> dp[3];
vector<vector<int>> adj;
vector<int> sales;

int getdp(int id, int state){
    if(dp[state][id] != 1LL<<32) return dp[state][id];
    long long &ret = dp[state][id];
    if(state == 1) ret = sales[id];
    else ret = 0;
    
    if(adj[id].size() == 0 && state == 0){
        return 0; 
    }
    if(adj[id].size() == 0 && state == 1) {
        return sales[id];
    }
    bool need = true;
    long long diff = 1LL<<32;
    for(int i = 0; i < adj[id].size(); ++i) {
        int nxt = adj[id][i];
        long long b = getdp(nxt,1);
        long long w = getdp(nxt,0);
        if(b >= w) diff = min(diff, b-w);
        if (b <= w) {
            need = false;
        }
        ret += min(b,w);
    }
    if (state == 0 && need) {
        ret+=diff;
    }
    return ret;
}

int solution(vector<int> sales, vector<vector<int>> links) {
    ::sales = sales;
    for(int i = 0; i < 3; ++i){
        dp[i].clear();
        dp[i].resize(sales.size(),1LL<<32);
    }
    adj.clear();
    adj = vector<vector<int>>(sales.size());
    for(auto it : links) {
        adj[it[0]-1].push_back(it[1]-1);
    }
    int nid = 0;
    int answer = 0;
    answer = min(getdp(0, 0), getdp(0,1));
    return answer;
}