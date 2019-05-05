#include<iostream>
#include<cstring>
#include<vector>

using namespace std;
int n;
int res = 0;
vector<int> w;
vector<int> nagu;

void dfs(int i){
    if(i == n){
        int t = 0;
        for(int i = 0; i < n; i++){t += nagu[i] <= 0;}
        res = res > t ? res : t;
        return;
    }

    if(nagu[i] <= 0) {
        dfs(i+1);
        return;
    }

    bool attack = false;

    for(int l = 0; l < n; l++){
        if(nagu[l] <= 0) continue;
        if(i == l) continue;
        attack = true;
        nagu[i] -= w[l];
        nagu[l] -= w[i];
        dfs(i+1);
        nagu[i] += w[l];
        nagu[l] += w[i];
    }

    if(!attack){
        dfs(i+1);
    }
}

int Do(){
    cin >> n;
    nagu.resize(n);
    w.resize(n);
    for(int i = 0; i < n; i++){
        cin >> nagu[i] >> w[i];
    }

    dfs(0);
    cout << res;
    return 0;
}
