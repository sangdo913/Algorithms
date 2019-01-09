//Meeting Time 
//https://www.acmicpc.net/problem/10678
#include<iostream>
#include<queue>
#include<set>
#include<cstring>

struct COD{
    int now, price, idx;
};

using namespace std;
bool operator<(const COD& a, const COD& b){
    return a.price > b.price;
}

priority_queue<COD> que;

int price[2][1000001];
vector<int> adj[20];
vector<int> info[2][20];
int n;

int bfs(){
    COD now = {1,0,0};
    COD now2 = {1,0,1};
    que.push(now); 
    que.push(now2);
    
    while(que.size()){
        now = que.top();que.pop();
        int rock = now.now;
        int p = now.price;
        int player = now.idx;

        if(p > 1000000) continue;

        else if(rock == n) {
            price[player][p] = true;
            if(price[player^1][p]) return p;
            continue;
        }

        for(int i = 0; i < adj[now.now].size(); i++){
            COD next;
            next.now = adj[now.now][i];
            next.price = p +info[player][now.now][i];
            next.idx = player;
            que.push(next);
        }
    }
    return -1;
}

int Do(){
    int m;
    cin >> n >> m;
    for(int i = 0; i < m; i++){
        int from, to;
        int price[2];
        cin >> from >> to >> price[0] >> price[1];

        adj[from].push_back(to);
        info[0][from].push_back(price[0]);
        info[1][from].push_back(price[1]);
    }

    int res = bfs();
    if(res == -1) cout <<"IMPOSSIBLE";
    else cout << res;
    return 0;
}