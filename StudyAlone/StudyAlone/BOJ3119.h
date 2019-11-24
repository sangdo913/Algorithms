#include<iostream>
#include<set>
#include<map>
#include<algorithm>
#include<vector>

using namespace std;

struct MYNODE{
    int x, xed, h, idx; 
    MYNODE(int x, int xed, int h, int idx):x(x), xed(xed), h(h), idx(idx) {}
    MYNODE(){}

} nodes[100011];

struct MYSKYLINE{
    int x, h, end;
    int idx;
};

int st[100000];
int res= 0;
struct cmp{
    bool operator() (const MYSKYLINE& x, const MYSKYLINE& y) const{
        if(x.x != y.x)  return x.x < y.x;
        if(x.end != y.end) return x.end > y.end;
        if(nodes[x.idx].xed != nodes[y.idx].xed) return nodes[x.idx].xed > nodes[y.idx].xed;
        return x.h > y.h;
    }
    bool operator() (int x, const MYSKYLINE&y) const{
        return x < y.x;
    }
    bool operator()  (const MYNODE & x, const MYNODE& y) const{
        if(x.x != y.x) return x.x < y.x;
        if(x.xed != y.xed) return  x.xed < y.xed;
        return x.h > y.h;
    }
};

vector<MYSKYLINE> line;
map<int, int> skyline;
int ain(){
    int n;
    cin >> n;

    for(int i = 0; i < n;++i){
        int x, w, h;
        cin >> x >> w >> h;
        nodes[i+1] = MYNODE(x,x +w, h, i+1);
        line.push_back({x,h,1,i+1});
        line.push_back({x+w,h,-1,i+1});
    }

    map<int,int> has;
    sort(line.begin(), line.end(), cmp());

    has[0] = 1;
    for(auto it  = line.begin(); it != line.end();){
        int x = it->x;
        auto it2 = upper_bound(line.begin(), line.end(), x,cmp());
        while(it != it2){
            has[it->h]+= it->end;
            if(has[it->h] == 0) has.erase(it->h);
            it++;
        }

        skyline[x] = has.rbegin()->first;
    }
    
    map<int, set<pair<int,int> > > require;
    map<int, int> have;
    for(auto it  = line.begin(); it != line.end();){
        int x = it->x;
        auto it2 = upper_bound(line.begin(), line.end(), x, cmp());

        while(it != it2){
            int h = it->h;
            int id = it->idx;

            if (it->end == 1) {
                require[h].insert({nodes[id].xed, id});
            }
            else {
                require[h].erase({nodes[id].xed, id});
                if (have[h] == id) have[h] = 0;
            }
            it++;
        }

        if (skyline[x] && !have[skyline[x]]) {
            int id = require[skyline[x]].rbegin()->second;
            have[skyline[x]] = id;
            st[res++] = id;
        }
    }
    
    sort(st, st + res);
    cout << res << '\n';
    for(int i = 0; i < res; ++i) cout << st[i] << ' ';
    return 0;
}
