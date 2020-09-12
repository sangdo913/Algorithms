#include <string>
#include<queue>
#include<iostream>
#include <vector>
#include<algorithm>

using namespace std;

int solution(int n, int s, int a, int b, vector<vector<int>> fares) {
    int answer = 0x3f3f3f3f;
    vector<vector<int>> aa(201, vector<int>(201,0x3f3f3f3f));
    vector<int> dist(201, 0x3f3f3f3f);
    vector<vector<int>> adj(n+1);
    vector<vector<int>>c(n+1);
    
    for(int i = 0; i < fares.size(); ++i){
        int f = fares[i][0], t = fares[i][1];
        int cost = fares[i][2];
        aa[f][t] = cost;
        aa[t][f] = cost;
        adj[f].push_back(t);
        adj[t].push_back(f);
        c[f].push_back(cost);
        c[t].push_back(cost);
    }
    for(int i = 1; i <= n; ++i) aa[i][i] =  0;
    for(int k = 1; k <= n; ++k){
        for(int i = 1; i <= n; ++i){
            for(int j = 1; j <= n; ++j){
                if(aa[i][j] > aa[i][k] + aa[k][j]){
                    aa[i][j] = aa[i][k] + aa[k][j];
                }
            }
        }
    }
    for(int i = 1; i <= n; ++i){
        if(aa[s][i] != 0x3f3f3f3f && aa[i][a] != 0x3f3f3f3f && aa[i][b] != 0x3f3f3f3f) answer = min(aa[s][i] + aa[i][a] + aa[i][b], answer);
    }
    
    return answer;
}