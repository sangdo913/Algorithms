#include<iostream>
#include<string>
#include<vector>

using namespace std;

string justification(vector<string> s, int w){
    int num = 0;
    for(int i = 0; i < s.size(); ++i) num += s[i].size();
    int remain = w - num;
    int even;
    if(s.size() > 1){
        even = remain / (s.size()-1);
        remain = remain - even * (s.size() - 1);
    }
    else even = w - s[0].size(), remain = 0;
    string res = s[0];
    for(int i = 0; i < even + (bool)remain; ++i){
        res.push_back(' ');
    }
    remain -= (bool)remain;
    
    for(int i =1; i < s.size(); ++i){
        res += s[i];
        for(int i = 0; i < even + (bool)remain; ++i){
            res.push_back(' ');
        }
        if(remain) remain--; 
    }
    while(res.size() != w) res.pop_back();
    return res;
}
class Solution {
public:
    vector<string> fullJustify(vector<string>& words, int maxWidth) {
        vector<string> res;
        if(words.size() == 0) return res;
        int n = words.size(); 
        vector<string> str;
        int num = -1;
        for(int i = 0; i <n; ++i){
            if(num + words[i].size() + 1 <= maxWidth){
                str.push_back(words[i]);
                num += 1+words[i].size();
            }
            else{
                res.push_back(justification(str, maxWidth));
                str.clear();
                num = -1;
                --i;
            }
        }
        string l;
        for(int i = 0; i < str.size(); ++i) {
            l+= str[i] + ' ';
        }
        l.pop_back();
        while(l.size() < maxWidth) l.push_back(' ');
        res.push_back(l);
        return res;
    }
};