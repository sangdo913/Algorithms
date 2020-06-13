#include<iostream>
#include<string>
#include<vector>

using namespace std;

int line[100];
int idx[100];
int r1, r2;
struct RES{
    int idx,line;
};

RES getdp(int i, string s, int n1, string s2, int n2){
    if(line[i] != -1) return {idx[i], line[i]};
    int m = s2.size();
    int n = s.size();
    line[i] = 0;
    int id1 = i, id2 = 0;
    int cnt = n2;
    while(1){
        if(id1 == n){
            line[i]++;
            id1 = 0; 
            n1--;
            if(n1 == 0) break;
        }
        if(s[id1] == s2[id2]){
            id2++;
            if(id2 == m){
                id2 = 0;
                cnt--;
                if(cnt == 0){
                    idx[i] = ++id1;
                    return{idx[i], line[i]};
                }
            }
        }
        id1++;
    }
    return {-1,-1};
}
bool allsame(string a, string b){
    int j = 0;
    if(a.size() % b.size()) return false;
    if(a.size() < b.size()) return false;
    for(int i = 0; i < a.size(); ++i, ++j){
        if(a[i] != b[j%b.size()]) return false;
    }
    return true;
}
class Solution {
public:
    int getMaxRepetitions(string s1, int n1, string s2, int n2) {
        if(!n1) return 0;
        string s;
        bool ch[256] = {};
        for(int i = 0; i < s2.size(); ++i) ch[s2[i]] = 1;
        for(int i = 0; i < s1.size(); ++i) if(ch[s1[i]]) s.push_back(s1[i]);
        int m = s2.size();
        int n = s.size();
        int id1 = 0, id2 = 0;
        int res = 0;
        int cnt = n2;
        int idx = 0;
        if(s.size() == 0) return 0;
        if(s.size()*n1 < s2.size()*n2) return 0;
        if(allsame(s, s2)) return s.size()*n1 / s2.size()/n2;
        for(int i = 0; i < n; ++i) line[i] = -1; 
        while(1){
            RES nxt = getdp(idx,s,n1, s2,n2);
            if(nxt.idx == -1) break;
            if(n1 - nxt.line <= 0) break;
            idx = nxt.idx;
            n1 -= nxt.line;
            res++;
            if(nxt.idx == n) n1--, idx = 0;
        }
        return res;
    }
};