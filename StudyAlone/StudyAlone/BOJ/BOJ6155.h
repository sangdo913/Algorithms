#include<iostream>
#include<vector>

using namespace std;

vector<int> adj[10001];
int mvisit[10001];
enum STATE{INSTALL, NOTNEED, NEED};
struct RES{
    STATE state;
    int res;
};

RES getnum(int p, int n){
    RES ret = {NEED, 0};
    mvisit[n] = 1;
    if(adj[n].size() == 0) return {NEED, 0};

    for(int i  = 0; i < adj[n].size(); ++i){
        int nn = adj[n][i];
        if(nn == p) continue;
        RES res = getnum(n, nn);
        if(res.state == NEED){
            ret.state = INSTALL;
        }
        else if(res.state == INSTALL){
            if(ret.state == NEED) ret.state = NOTNEED;
        }
        ret.res += res.res;
    }
    if(ret.state == INSTALL) ret.res++;
    return ret;
}

int main(){
    freopen("0Text.txt", "r", stdin);
    int n;
    cin >> n;
    int ret = 0;
    for (int i = 1; i < n; ++i){
        int a, b;
        cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    RES res = getnum(-1, 1);
    if(res.state == NEED) ret++;
    ret += res.res;
    cout << ret;
    return 0;
}