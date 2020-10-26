#include<iostream>
#include<vector>
using namespace std;

int p[10001];

int findp(int i){
    if(p[i] < 0) return i;
    return p[i] = findp(p[i]);
}

void join(int a, int b){
    int pa = findp(a), pb = findp(b);
    if(pa == pb) return;
    if(p[pa] < p[pb]) pa^=pb^=pa^=pb;
    p[pb] += p[pa];
    p[pa] = pb;
}

bool isfirst = 0;
class Solution {
public:
    vector<bool> areConnected(int n, int threshold, vector<vector<int>>& queries) {
        ios_base::sync_with_stdio(0);
        cin.tie(0);
        cout.tie(0);
        for(int i =1; i <= n; ++i) p[i] = -1;
        for(int i =threshold + 1; i <= 2*n; ++i) {
            for(int j = 2*i;  j <= n; j+=i){
                join(i,j);
            }
        }
        int l = queries.size();
        vector<bool> res(l);
        for(int i = 0; i < l; ++i){
            res[i] = findp(queries[i][0]) == findp(queries[i][1]);
        }
        return res;
    }
};