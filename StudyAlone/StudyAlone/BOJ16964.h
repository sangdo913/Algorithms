#include<iostream>
#include<queue>
#include<algorithm>
#include<map>

using namespace std;

vector<int> vec[100001];
int res[100000];
int order[100001];

int n, idx;
bool check[100001];

bool dfs(int now){
    check[now] = true;
    if(res[idx++] != now) return false;
    priority_queue<pair<int, int> > pq;

    for(int i = 0; i < vec[now].size(); i++){
        int next = vec[now][i];
        pq.push({-order[next], next});
    }

    while(pq.size()){
        int next = pq.top().second; pq.pop();
        if(check[next]) continue;
        bool res = dfs(next);
        if(!res) return false;
    }
    return true;
}

int Do(){
    ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);

    cin >> n;
    for(int i = 0; i < n-1; i++){
        int f, t;
        cin >> f >> t;
        vec[f].push_back(t);
        vec[t].push_back(f);
    }

    for(int i = 0; i < n; i++){
        cin >> res[i];
        order[res[i]] = i;
    }
    cout << dfs(1);
    return 0;
}