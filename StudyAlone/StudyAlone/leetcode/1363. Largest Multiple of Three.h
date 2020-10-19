#include<iostream>
#include<vector>
#include<string>
#include<algorithm>
#include<queue>

using namespace std;

class Solution {
public:
    string largestMultipleOfThree(vector<int>& digits) {
        int cnt[11] = {};
        int remain[3][6] = {{},{1,4,7,2,5,8},{2,5,8,1,4,7}};
        
        int allsum = 0;
        for(int i = 0; i < digits.size(); ++i) {
            allsum += digits[i];
            cnt[digits[i]]++;
        }
        int cur = 0;
        int r = allsum%3;
        while(allsum %3) {
            if(cnt[remain[r][cur]]) {
                cnt[remain[r][cur]]--;
                allsum -= remain[r][cur];
            }
            else cur++;
        }
        
        string res;
        for(int i = 9; i >= 0; --i){
            while(cnt[i]--){
                res += i+'0';
            }
        }
        return res[0] == '0' ? "0" : res;
    }
};