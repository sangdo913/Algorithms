#include<iostream>
#include<map>
#include<vector>
using namespace std;
map<pair<int,int>, int> mp;
vector<vector<int>> adj;
int n;
vector<int> pa;
vector<int> cycle;

int findp(int a){
    if(pa[a] < 0) return a;
    return pa[a] = findp(pa[a]);
}

bool join(int a, int b){
    int ppa = findp(a), ppb = findp(b);
    if(ppa == ppb) return true;
    
    if(pa[ppa] < pa[ppb]) ppa^=ppb^=ppa^=ppb;
    pa[ppb] += pa[ppa];
    pa[ppa] = ppb;
    return false;
}

bool iscycle(int a, int std){
    if(a == std) return true;
    bool res = false;
    for(int i = 0; i < adj[a].size(); ++i) {
        res = iscycle(adj[a][i], std);
    }
    return res;
}

class Solution {
public:
    vector<int> findRedundantDirectedConnection(vector<vector<int>>& edges) {
        mp.clear();
        adj.clear();
        n = edges.size();
        pa.clear();
        pa.resize(n+1, -1);
        vector<int> parent(n+1);
        adj.resize(n+1);
        vector<int> inorder(n+1);
        cycle.clear();
        cycle.resize(n+1);
        for(int i = 0; i < edges.size(); ++i){
            adj[edges[i][1]].push_back(edges[i][0]);
            mp[{edges[i][0], edges[i][1]}] = i;
        }
        
        for(int i = 1; i <= n; ++i){
            if(adj[i].size() == 2){
                bool chk1 = iscycle(adj[i][0], i);
                bool chk2 = iscycle(adj[i][1], i);
                int eid;
                if(chk1) eid = mp[{adj[i][0],i}];
                else if(chk2) eid = mp[{adj[i][1],i}];
                else eid = max(mp[{adj[i][0],i}], mp[{adj[i][1],i}]);
                return edges[eid];
            }
        }
        for(int i = 0; i < edges.size(); ++i){
            if(join(edges[i][0], edges[i][1])) return edges[i];
        }
        
        return vector<int>();
    }
};