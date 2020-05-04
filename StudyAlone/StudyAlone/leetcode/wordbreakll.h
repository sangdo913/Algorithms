#include<iostream>
#include<vector>
#include<string>

using namespace std;

vector<bool> mvisit;
vector<vector<string>> dp;
struct NODE{
    int idx;
    int child[26];
    NODE()  {
        idx = -1;
        for(int i = 0; i < 26; ++i) child[i] = 0;
    }
};
vector<NODE> nodes;
int nid = 1;
int conv[256];
vector<string> ret;

void getdp(vector<string>& wordDict, string &s, int l){
    if(l == s.size()){
       return;
    }
    if(mvisit[l]) return;
    mvisit[l] = 1;
    
    int cur = 0;
    for(int i = l; i < s.size(); ++i){
        int c = conv[s[i]];
        if(nodes[cur].child[c] == 0) break;
        cur = nodes[cur].child[c];
        if(nodes[cur].idx != -1) {
            getdp(wordDict, s, i+1);
            for(auto it : dp[i+1]){
                dp[l].push_back(wordDict[nodes[cur].idx] + " " + it);
            }
        }
    }
}

class Solution {
public:
    vector<string> wordBreak(string s, vector<string>& wordDict) {
        int cnt = 0;
        nid = 1;
        ret.clear();
        nodes.clear();
        nodes.resize(100);
        mvisit.clear();
        mvisit.resize(s.size(), false);
        dp.clear();
        dp.resize(s.size()+1);
        dp[s.size()].push_back("");
        for(int i = 'a'; i<='z'; ++i) conv[i] = cnt++;
        for(int i = 0; i < 26; ++i) nodes[0].child[i] = 0;
        for(int i = 0; i < wordDict.size(); ++i){
            int cur = 0;
            for(int j = 0; j < wordDict[i].size(); ++j){
                int c = conv[wordDict[i][j]];
                if(!nodes[cur].child[c]){
                    if(nid == nodes.size()){
                        nodes.push_back(NODE());
                    }
                    nodes[cur].child[c] = nid++;
                }
                cur = nodes[cur].child[c];
            }
            nodes[cur].idx = i;
        }
        getdp(wordDict,s, 0);
        for(auto &it : dp[0]){
            it.pop_back();
        }
        
        return dp[0];
    }
};