#include<iostream>
#include<algorithm>
#include<vector>
#include<string>
using namespace std;
int max_table[256];
int min_table[256];
int mskip[256];

class Solution {
public:
    vector<string> maxNumOfSubstrings(string s) {
        for(int i = 'a'; i <= 'z'; ++i) {
                mskip[i] = 0;
                min_table[i] = 0x3f3f3f3f;
        }
        for(int i = 0; i < s.size(); ++i){
            max_table[s[i]] = i;
            min_table[s[i]] = min(min_table[s[i]], i);
        }
        
        vector<pair<int,int>> v;
        
        for(int i = 'a'; i <= 'z'; ++i) {
            bool skip = false;
            if(min_table[i] == 0x3f3f3f3f) continue;
            for(int j = min_table[i]; j <= max_table[i]; ++j) {
                if(min_table[s[j]] < min_table[i]) {
                    skip = true;
                    break;
                }
                max_table[i] = max(max_table[i], max_table[s[j]]);
            }
            if(!skip){
                v.push_back({max_table[i], i});
            }
        }
        sort(v.begin(), v.end());
        
        int cur = -1;
        vector<string> res;
        for(auto it : v){
            if(cur < min_table[it.second]){
                res.push_back(s.substr(min_table[it.second], max_table[it.second] - min_table[it.second]+1));
                cur = max_table[it.second];
            }
        }
        return res;
    }
};