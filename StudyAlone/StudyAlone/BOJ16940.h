#include<iostream>
#include<queue>
#include<vector>
#include<algorithm>

using namespace std;

int order[100001], n;
int res[100001], rlen;
int in[100001];

priority_queue<pair<int, int> > pq;
queue<int> que;
bool visit[100001];
vector<int> adj[100001];

int Do(){
    cin >> n;
    for(int i = 0; i < n-1; i++){
        int f, t;
        cin >> f >> t;
        adj[f].push_back(t);
        adj[t].push_back(f);
    }

    for(int i = 0; i < n; i++){
        int  idx;

        cin >> idx;
        in[i] = idx;
        order[idx] = i;
    }

    que.push(1);
    visit[1] = true;

    while(que.size()){
        int now = que.front(); que.pop();

        res[rlen++] = now;

        for(int i = 0; i < adj[now].size(); i++){
            int next = adj[now][i];

            if(visit[next]) continue;
            visit[next] = true;

            pq.push({-order[next], next});
        }

        while(pq.size()){
            int next = pq.top().second; pq.pop();
            que.push(next);
        }
    }

    for(int i = 0;i < n; i++){
        if(in[i] != res[i]) return !(cout << 0);
    }
    cout << 1;
    return 0;
}