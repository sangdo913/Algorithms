#include<iostream>
#include<string>
#include<vector>
using namespace std;

class Solution {
public:
    int strongPasswordChecker(string s) {
        int cnt[4] ={};
        for(int i = 0; i < s.size(); ++i){
            if('a' <= s[i] && s[i]<='z') cnt[0]++;
            else if('A' <= s[i] && s[i]<='Z') cnt[1]++;
            else cnt[2]++;
        }

        int res = 0;
        int need = 0;
        int change = 0;
        int del = 0;
        int size = s.size();
        int beforeidx = 0;
        for(int i = 0; i < 3; ++i) need += !cnt[i];
        int continuecnt = 0;
        for(int i = 0; i < s[i]; ++i){
            if(s[i] == s[beforeidx]){
                continuecnt++;
                if(continuecnt == 3){
                    change++;
                    if(size < 6) {
                        ++size;
                    }
                    else if(20 < size) --size;
                    if(need) --need;
                    before = 0;
                    continuecnt = 0;
                }
            }
            else{
                before = s[i];
                continuecnt = 1;
            }
        }

        if(size < 6){
            res = need < 6-s.size() ? 6-s.size() : need;
        }
        else if(size > 20){
            res = s.size() - 20 + need;
        }
        else{
            res = need;
        }
        return res + change;
    }
};

int main(){
    freopen("0Text.txt", "r", stdin);
    string s;
    cin >> s;
    cout << Solution().strongPasswordChecker(s) << endl;
    return 0;
}
