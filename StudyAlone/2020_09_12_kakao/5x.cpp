#include <string>
#include <vector>
#include<sstream>
#include<iostream>
#include<algorithm>

using namespace std;

long long lazy[360001*4];
long long nodes[3600001*4];

void setlazy(int id, int s, int e){
    nodes[id] += lazy[id]*(e-s+1);
    if(s!=e){
        lazy[id*2] += lazy[id];
        lazy[id*2+1] += lazy[id];
    }
    lazy[id] = 0;
}


void init(int id, int l, int r, int s, int e){
    if(r < s || e < l) return;
    lazy[id] = 0;
    nodes[id] = 0;
    if(l == r) return;
    int m  = (l+r)/2;
    init(id*2, l,m, s, e);
    init(id*2+1, m+1, r, s,e);
}

void sum(int id, int l, int r, int s, int e){
    if(e < l || r < s) return;
    setlazy(id, l,r);

    if(s<=l && r <= e) {
        lazy[id] += 1;
        setlazy(id, l,r);
        return;
    }
    int m = (l+r)/2;
    sum(id*2, l, m, s, e);
    sum(id*2+1, m+1,r,s,e);
    nodes[id] = nodes[id*2] + nodes[id*2+1];
}

long long getsum(int id, int l, int r, int s, int e){
    if(e < l || r < s) return 0;
    setlazy(id, l,r);
    if(s<=l && r <= e) {
        return nodes[id];
    }
    int m = (l+r)/2;
    return getsum(id*2, l,m, s,e) + getsum(id*2+1, m+1,r,s,e);
}

int tosec(string s){
    for(int i = 0; i < s.size(); ++i) s[i]-='0';
    return s[0]*36000 + s[1]*3600 + s[3]*600 + s[4]*60 + s[6]*10+s[7];
}
string stostr(int sec){
    string res;
    res.resize(8);
    res[2] = res[5] = ':';
    int h = sec/3600;
    res[0] = h/10 +'0';
    res[1] = h%10 + '0';
    sec %= 3600;
    int m = sec/60;
    res[3] = m/10 + '0';
    res[4] = m%10 + '0';
    sec %=60;
    res[6] = sec/10+'0';
    res[7] = sec%10 + '0';
    return res;
}

string solution(string play_time, string adv_time, vector<string> logs) {
    string answer = "";
    int pt = tosec(play_time);
    int at = tosec(adv_time);
    init(1,0,pt,0,pt);
    int cnt = 0;
    for(auto it : logs){
        string t;
        stringstream stream;
        stream.str("");
        stream.str(it);
        getline(stream, t, '-');
        int st = tosec(t);
        getline(stream,t, '-');
        int et = tosec(t)-1;
        sum(1,0,pt, st,et);
    }
    long long mmax = -1;
    for(int i = 0; i <= pt-at; ++i){
        long long res = getsum(1,0,pt,i,i+at-1);
        if(mmax < res){
            mmax = res;
            answer = stostr(i);
            cout << answer << ' ' << res << endl;;
        }
    }

    return answer;
}


int main(){
    freopen("0Text.txt", "r", stdin);
    string ptime = "99:59:59";
    string atime = "10:00:00";
    string log = "00:00:00-99:59:59";
    vector<string> v(300000, log);

    bool use_tc = true;
    if(use_tc){
        v.clear();
        cin >> ptime;
        cin >> atime;
        int m;
        cin >> m;
        while(m--) {
            string s;
            cin >> s;
            v.push_back(s);
        }
    }
    string s = solution(ptime, atime, v);
    cout << s << endl;
    return 0;
}