#include<iostream>
#include<queue>
#include<vector>

using namespace std;
struct INFO{
    int i;
    int dist;
};

int fire[1000];
int main(){
    freopen("0Text.txt", "r", stdin);
    int C;
    cin >> C;
    for(int tc = 1; tc <= C; ++tc){
        int v, e, n, m;
        cin >> v >> e >> n >> m;
        vector<int> dist(v+1,0x3f3f3f3f);
        vector<vector<INFO>> info(v+1, vector<INFO>());

        for(int i = 0; i < e; ++i){
            int f, t, d;
            cin >> f >> t >> d;
            info[f].push_back({t,d});
            info[t].push_back({f,d});
        }

        priority_queue<pair<int, int>> pq;
        for(int i = 0; i < n; ++i) cin >> fire[i];
        for(int i = 0; i < m; ++i) {
            int firehouse;
            cin >> firehouse;
            pq.push({0,firehouse});
            dist[firehouse] = 0;
        }

        while(!pq.empty()){
            pair<int, int> now = pq.top(); pq.pop();
            int d = -now.first;
            int id = now.second;
            if (dist[id] < d){ continue; }

            for(int i = 0; i < info[id].size(); ++i){
                int next = info[id][i].i;
                int nextd = d + info[id][i].dist;

                if(nextd < dist[next]){
                    dist[next] = nextd;
                    pq.push({-nextd, next});
                }
            }
        }
        int res = 0;
        for(int i = 0; i < n; ++i){
            res += dist[fire[i]];
        }
        cout << res << endl;
    }
    return 0;
}