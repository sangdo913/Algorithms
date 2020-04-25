#include<iostream>
#include<algorithm>
#include<string>
#include<set>
#include<vector>
using namespace std;
vector<int> mvisit;
vector<vector<string>> res;
int n;
set<string> se;

bool getdp(string &s, vector<string>&wordDict,int i){
    if(i == n) return true;
    if(mvisit[i] !=-1){ return mvisit[i];}
    mvisit[i] = 0;
    string str;
    for(int j = i; j < n; ++j){
        str.push_back(s[j]);
        if(find(wordDict.begin(), wordDict.end(), str) != wordDict.end()){
            if(getdp(s,wordDict, j+1)){
                for(auto it: res[j+1]){
                    res[i].push_back(str + string(" ") + it);
                    mvisit[i] = true;
                }
            }
        }
    }
    return mvisit[i];
}

class Solution {
public:
    vector<string> wordBreak(string s, vector<string>& wordDict) {
        se.clear();
        mvisit.clear();
        mvisit.resize(s.size(),-1);
        res.clear();
        n = s.size();
        res.resize(s.size()+1);
        res[n].push_back(string(""));
        sort(wordDict.begin(), wordDict.end());
        getdp(s,wordDict, 0);
        for(auto &it : res[0]) it.pop_back();
        
        return res[0];
    }
};