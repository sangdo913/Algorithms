#include<iostream>
#include<string>

using namespace std;

int cnt[256] = {-1,};
class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        for(int i = 0; i < 256; ++i) cnt[i] = -1;
        int i = 0;
        int n = s.size();
        int res = 0;
        for(int j = 0; j < n ; i = cnt[s[j]]+1){
            while(j < n && cnt[s[j]] < i) cnt[s[j++]] = j; 
            if(res < j-i) res = j-i;
        } 
        return res;
    }
};