#include<iostream>
#include<string>

using namespace std;

int charcnt[256];
bool issil(string s){
    int cnt = 0;
    int pos = s.size();
    int st = s[0] == '-' || s[0] == '+';
    if(s.size() == st) return false;
    bool digit = false;
    for(int i = st; i < s.size(); ++i){
        if('0'<= s[i] && s[i] <= '9') {digit = true; continue;}
        if(s[i] == '.') cnt++, pos = i;
        else return false;
    }
    if(!digit) return false;
    if(cnt > 1) return false;
   return true; 
}

bool isjung(string s){
    int st = s[0] == '+' || s[0] == '-';
    if(s.size() == st) return false;
    for(int i = st; i < s.size(); ++i){
        if(s[i]<'0' || '9' < s[i]) return false;
    }
    return true;
}

class Solution {
public:
    bool isNumber(string s) {
        int pos[128];
        bool allnum = true;
        bool digit = false;
        bool ret = true;
        auto st = s.begin();
        auto ed = s.rbegin();
        while(st != s.end() && *st == ' ') st++;
        while(ed != s.rend() && *ed == ' ') ed++;
        int fr = st - s.begin();
        int en = s.size() - (ed - s.rbegin());
        if(fr >= en) return false;

        s = string(s.begin() + fr, s.begin() + en);

        for(int i = 0; i < 256; ++i) charcnt[i] = 0;
        pos['e'] = pos['.'] = s.size();
        for(int i = 0; i < s.size(); ++i){
            if(s[i] < '0' || s[i] > '9') {
                if(s[i] == 'e' || s[i] =='+' || s[i]== '-' || s[i] == '.'){
                    charcnt[s[i]]++;
                    allnum = false;
                    pos[s[i]] = i;
                }
                else return false;
            }
            else digit = true;
        }
        if(!digit) return false;
        if(charcnt['e'] > 1) return false;
        else if(pos['e'] == 0) return false;
        else if(pos['e'] == s.size()-1) return false;

        if(charcnt['.'] > 1) return false;
        if(charcnt['e']){
            string le = string(s.begin(), s.begin() + pos['e']);
            string ri = string(s.begin() + pos['e']+1, s.end());
            if(!issil(le) || !isjung(ri)) return false;
        }
        else{
            if(!issil(s)) return false;
        }
        return true; 
    }
};

int main(){
    freopen("0Text.txt", "r", stdin);
    string s;
    getline(cin, s);
    cout << Solution().isNumber(s);
    return 0;
}