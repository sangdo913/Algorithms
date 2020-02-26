#include<iostream>
#include<queue>
#include<vector>

using namespace std;
struct INFO{
    int i;
    double dist;
};


int main(){
    // freopen("0Text.txt", "r", stdin);
    ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    int T;
    cin >> T;
    for(int tc= 1; tc <= T; ++tc){
        int n, m;
        cin >> n >> m;
        vector<vector<INFO> > info;
        vector<double> dist;
        dist.resize(n, -1);
        info.resize(n,vector<INFO>());
        for(int i = 0; i < m; ++i){
            int from, to;
            double d;

            cin >> from >> to >> d;

            info[from].push_back({to,d});
            info[to].push_back({from, d});
        }

        priority_queue<pair<double,int>> pq;
        pq.push({-1, 0});
        dist[0] = 1;
        while(true){
            pair<double, int> now = pq.top(); pq.pop();
            int id = now.second;
            double d = -now.first;
            if(dist[id] < d) continue;
            if(id == n-1){
                cout.setf(ios_base::fixed);
                cout.precision(10);
                cout << d <<'\n';
                break;
            }
            for(int i = 0; i < info[id].size(); ++i){
                int next = info[id][i].i;
                double nextdist = d*info[id][i].dist;
                if(dist[next] == -1 || nextdist < dist[next]){
                    dist[next] = nextdist;
                    pq.push({-nextdist, next});
                }
            }
        }
    }
    return 0;
}