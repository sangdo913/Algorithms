//Wormholes
//https://www.acmicpc.net/problem/9874
#include<iostream>
#include<vector>
#include<algorithm>
#include<cstring>

using namespace std;

struct COD{
    int x, y;
};

int adj[12];
int worm[12];

int visit;
int n;

bool iscycle(int node, int cnt){
    if(cnt > n) return true;
    visit |= 1 << node;

    if(adj[node] == -1) return false;
    
    int nn = worm[adj[node]];
    if(iscycle(nn,cnt+1)) return true;

    return false;
}

bool check(){
    visit = 0;
    for(int i = 0; i < n; i++){
        if(visit & (1<<i)) continue;
        if(iscycle(i, 1)) return true;
    }

    return false;
}

bool operator<(const COD& c1, const COD& c2){
    if(c1.y == c2.y) return c1.x < c2.x;

    return c1.y < c2.y;
}

vector<COD> cods;
int res;

void func(int visit, int idx){
    if(visit == ((1<<n) -1)){ 
        res += check(); 
        return;
    }

    while(((1<<idx) & visit)) idx++; 

    for(int i = idx + 1 ; i < n; i++){
        if(((1 << i) & visit) == 0){
            visit += 1<<i;
            visit += 1 << idx;
            worm[i] = idx;
            worm[idx] = i;

            func(visit, idx+1);

            visit ^= 1 << i;
            visit ^= 1 << idx;
        }
    }
}

int Do(){
    memset(adj, -1,sizeof(adj));
    cin >> n;

    for(int i = 0; i < n; i++) {
        int x, y;

        cin >> x >> y;
        cods.push_back({x,y});
    }

    sort(cods.begin(),cods.end());

    for(int i = 0; i < n-1; i++){
        if(cods[i].y == cods[i+1].y) adj[i] = i+1;
    }

    func(0,0);
    cout << res;

    return 0;
}