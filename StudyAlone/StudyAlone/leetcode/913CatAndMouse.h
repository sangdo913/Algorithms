#include<iostream>
#include<vector>
#include<algorithm>
#include<queue>

using namespace std;
#define rint register int
int myvisit[50][50][2];
int nodevisit[50][50][2];
int nodecnt[50][50][2];

int tc; 
vector<vector<int>> *g;
struct NODE{
    int c, m, turn;
}

int go(int turn, int c, int m){
    int &ret = myvisit[c][m][turn];
    if(!m) return tc+2;
    if(c == m) return tc + 1;
    if(ret >= tc) return ret;

    int pos = turn ? c: m;
    bool draw = false;

    while(nodevisit[c][m][turn] != (*g)[pos].size()){
        int n = (*g)[pos][nodevisit[c][m][turn]++];
        int nc = turn ? n : c;
        int nm = turn ? m : n;
        if(!nc) continue;

        int res = go(turn^1, nc,nm);
        if(turn && res == tc+1){
            return ret = tc + 1;
        }
        if(!turn && res == tc + 2){
            return ret = tc + 2;
        }
        if(res == tc) draw = true;
    }
    if(!draw)
        for(int i = 0; i < (*g)[pos].size(); ++i) {
            int n = (*g)[pos][i];
            int nc = turn ? n : c;
            int nm = turn ? m : n;
            if(!nc) continue;
            if(myvisit[nc][nm][turn^1] < tc){
                draw = true;
                break;
            }
        }

    if(draw) return ret = tc;
    else return ret = turn ? tc+2 : tc + 1;
}

class Solution {
public:
    int catMouseGame(vector<vector<int>>& graph) {
        g = &graph;

        tc+=4;
        for(rint i = 0; i < graph.size(); ++i){
            for(rint j = 0; j < graph.size(); ++j)
                nodecnt[i][j][1] = graph[i].size(), nodecnt[i][j][0] = graph[j].size();
        }
        for(rint i = 0; i < graph.size(); ++i){
            for(rint j = 0; j < graph.size(); ++j) nodevisit[i][j][0] = nodevisit[i][j][1] = 0;
        }
        int res = go(0,2,1);
        if(res == tc + 2) res = 1;
        else if(res == tc+1) res = 2;
        else res = 0;

        return res;
    }
};

int main(){
    freopen("0Text.txt", "r", stdin);
    vector<vector<int> > vec;
    int n;
    cin >> n;
    vec.resize(n);
    for(int i = 0; i < n; ++i){
        int m;
        cin >> m;
        vec[i].resize(m);
        for(int j = 0; j < m; ++j){
            cin >> vec[i][j];
        }
    }
    cout << Solution().catMouseGame(vec);

    return 0;
}