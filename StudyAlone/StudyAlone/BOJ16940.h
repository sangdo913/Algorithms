#include<iostream>
#include<queue>
#include<vector>

using namespace std;

int order[100001], n;
int cnt[100001];
int Prev[100001];

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
        cin >> order[i];
    }

    que.push(1);
    visit[1] = true;

    while(que.size()){
        int now = que.front(); que.pop();

        for(int i = 0; i < adj[now].size(); i++){
            int next = adj[now][i];

            if(visit[next]) continue;
            visit[next] = true;
            Prev[next] = now;
            cnt[now]++;

            que.push(next);
        }
    }

    que.push(0);
    cnt[0] = 1;

    for(int i = 0; i < n; i++){
        int p = Prev[order[i]];

        if(que.front() !=p){
            return!(cout << 0);
        }
        else{
            if(cnt[order[i]]) que.push(order[i]);
        }
        cnt[p]--;
        if(cnt[p] == 0) que.pop();
    }

    cout << 1;
    return 0;
}