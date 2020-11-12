#include<iostream>
#include<string>
#include<map>
#include<vector>

using namespace std;

map<string, int> mp;
vector<int> node;
void clear(){

}

struct NODE{
    string ss;
    bool valid;
    int str;
    int len;
    int cnt;
} nodes[50000];
int nid;
vector<int> strings;

void init(){
    mp.clear();
    strings.clear();
    nid = 0;
}

void add_str (char *str, int l) {
    string s(str);
    int sid = 0;
    if(mp.find(s) == mp.end()) {
        sid = mp[s] = nid++;
        nodes[sid].ss = s;  
        nodes[sid].cnt = 0;
        strings.push_back(sid); 
        nodes[sid].valid = false;
    }
    else {
        sid = mp[s];
    }
    NODE &nn = nodes[sid];
    if(nn.valid == false){
        nn.valid = true;
        nn.cnt = 1;
    }
    else {
        nn.cnt++;
    }
}

int get_str (char *str, int l){
    int res = 0;
    int s= 0 , e = 0;
    int el =0;
    string a(str);
    while(e < l && str[e] != '*') e++; 
    bool cascade = l == e;
    el = l-1-e;
    for(int i = 0; i < strings.size(); ++i) {
        if(!nodes[strings[i]].valid) continue;
        if(nodes[strings[i]].ss.size() < l-1) continue;

        bool find = true;
        string &s = nodes[strings[i]].ss;
        if(cascade && a != s){
            find = false;
        }
        for(int i = 0; i < e; ++i) {
            if(str[i] != s[i]) {
                find = false;
                break;
            }
        }

        if(find) {
            for(int i = 0; i < el; ++i){
                if(str[l-1-i] != s[s.size()-1-i]) {
                    find = false;
                    break;
                }
            }
        }
        if(find){
            res+= nodes[strings[i]].cnt; 
        }
    }
    return res;
}

int remove_str (char*str, int l) {
    int res = 0;
    int s= 0 , e = 0;
    int el =0;
    while(e < l && str[e] != '*') e++; 
    bool cascade = e == l;
    el = l-1-e;
    string a(str);
    for(int i = 0; i < strings.size(); ++i) {
        if(!nodes[strings[i]].valid) continue;
        if(nodes[strings[i]].ss.size() < l-1) continue;
        bool find = true;

        string &s = nodes[strings[i]].ss;
        if(cascade && a != s){
            find = false;
        }
        for(int i = 0; i < e; ++i) {
            if(str[i] != s[i]) {
                find = false;
                break;
            }
        }

        if(find) {
            for(int i = 0; i < el; ++i){
                if(str[l-1-i] != s[s.size()-1-i]) {
                    find = false;
                    break;
                }
            }
        }
        if(find) {
            res+= nodes[strings[i]].cnt;
            nodes[strings[i]].cnt = 0;
            nodes[strings[i]].valid = false;
        }
    }
    return res;
}