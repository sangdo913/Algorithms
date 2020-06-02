#include<iostream>
#include<string>
using namespace std;

#define MOD 1000000007

class Solution {
public:
    int numDecodings(string s) {
        long long prev = 1, pprev = 1;
        long long res = 1;
        if(s[0] == '*') prev = 9;
        else if(s[0] == '0') prev = 0;
        else prev = 1;
        for(int i = 1; i < s.size(); ++i){
            long long nxt = 0;
            //2개
            if(s[i-1] == '*'){
                if(s[i] == '*'){
                    nxt = pprev*15%MOD;
                }
                else if(s[i] <= '6') nxt = 2*pprev%MOD;
                else nxt = pprev;
            }
            else if(s[i-1] == '1'){
                if(s[i] == '*') nxt = pprev*9%MOD; 
                else nxt = pprev;
            }
            else if(s[i-1] == '2'){
                if(s[i] == '*') nxt = pprev*6%MOD;
                else if(s[i] <= '6') nxt = pprev;
            }
            //1개
            if(s[i] == '*'){
                nxt = (nxt + prev*9)%MOD;
            }
            else if(s[i] != '0'){
                nxt = (nxt +prev)%MOD;
            }
            pprev = prev;
            prev = nxt;
        }
        return prev;
    }
};