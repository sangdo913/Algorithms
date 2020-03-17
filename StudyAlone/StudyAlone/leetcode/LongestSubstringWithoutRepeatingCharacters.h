#include<iostream>
#include<string>

using namespace std;

class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        int cnt[256] = {0,};
        int i = 0;
        int n = s.size();
        int res = 0;
        
        for(int j = 0; j < n; ++j){
            while(i < n && !cnt[s[i]]) cnt[s[i++]]++;
            cnt[s[j]]--;
            if(res < i-j) res = i-j;
        } 
        return res;
    }
};