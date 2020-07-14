#include<iostream>
#include<vector>
#include<string>

using namespace std;

vector<int> kmp;
class Solution {
public:
    string shortestPalindrome(string s) {
        if(s.size() == 0) return string();
        kmp.clear();
        int j = -1;
        string str = s + '#' + string(s.rbegin(), s.rend());
        int n = str.size();
        kmp.resize(n);
        kmp[0] = -1;
        for(int i = 0; i < n; ++i){
            kmp[i] = j;
            while(j != -1 && str[j] != str[i]) {
                j = kmp[j];
            }
            ++j;
        }
        string res = string(str.begin() + n/2+1, str.begin() + n - j) + s;
        return res;
    }
};