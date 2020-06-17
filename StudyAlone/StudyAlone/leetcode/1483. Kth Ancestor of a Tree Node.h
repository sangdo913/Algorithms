#include<iostream>
#include<vector>
#include<queue>

using namespace std;

class TreeAncestor {
public:
    vector<int> d;
    vector<vector<int>> adj;
    vector<vector<int>> p;
    TreeAncestor(int n, vector<int>& parent) {
        int b = 0;
        for(int i = 1; i <= n; i<<=1, b++);
        p.clear();
        p.resize(n, vector<int>(b,0));
        adj.clear();
        adj.resize(n);
        d.clear();
        d.resize(n);
        queue<int> Q;
        for(int i = 1; i < n; ++i){
            adj[parent[i]].push_back(i);
            p[i][0] = parent[i];
        }
        p[0][0] = -1;
        Q.push(0);
        
        while(!Q.empty()){
            int now = Q.front(); Q.pop();
            for(int i = 0; i < adj[now].size(); ++i){
                int nn = adj[now][i];
                d[nn] = d[now]+1;
                Q.push(nn);
            }
        }
        for(int i = 1; i < b; ++i){
            for(int j = 0; j < n; ++j){
                int pp = p[j][i-1];
                if(pp == -1) p[j][i] = -1;
                else p[j][i] = p[pp][i-1]; 
            }
        }
    }
    
    int getKthAncestor(int node, int k) {
        int i = 0;
        
        while(k){
            if(k&1){
                node = p[node][i];
            }
            k>>=1;
            ++i;
            if(node == -1) return node;
        }
        return node;
    }
};

/**
 * Your TreeAncestor object will be instantiated and called as such:
 * TreeAncestor* obj = new TreeAncestor(n, parent);
 * int param_1 = obj->getKthAncestor(node,k);
 */