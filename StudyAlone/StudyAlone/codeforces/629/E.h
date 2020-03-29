#include<iostream>
#include<vector>
#include<algorithm>
#include<queue>

using namespace std;
vector<int> c[200001];
int depth[200001];
long long check[200001];
int lca[30][200001];

int main(){
    ios_base::sync_with_stdio(0), cout.tie(0), cin.tie(0);
    freopen("0Text.txt", "r", stdin);
    int n, m;
    cin >> n >> m;
    for(int i = 1; i < n; ++i){
        int p, n;
        cin >> p >> n;
        c[p].push_back(n);
        c[n].push_back(p);
    }
    queue<int> Q;
    Q.push(1);
    depth[1] = 1;
    while(!Q.empty()){
        int now = Q.front();Q.pop(); 
        for(int i = 0; i < c[now].size(); ++i){
            int nn = c[now][i];
            if(depth[nn]) continue;
            depth[nn] = depth[now] +1;
            lca[0][nn] = now;
            Q.push(nn);
        }
    }
    int bn = 0;
    int i = 1;
    while(i < n){
        bn++;
        i<<=1;
    }
    for(int i = 1; i <=bn; ++i){
        for(int j = 1; j <= n; ++j){
            lca[i][j] = lca[i-1][lca[i-1][j]];
        }
    }

    while(m--){
        int k;
        cin >> k;
        vector<pair<int,int>> vec;
        for(int i = 0; i < k; ++i){
           int nn;
           cin >> nn;
           vec.push_back({depth[lca[0][nn]], lca[0][nn]});
        }
        sort(vec.begin(),vec.end());
        for(int i = 1; i < vec.size(); ++i){
            int a = vec[i-1].second;
            int b = vec[i].second;
            int diff = vec[i].first - vec[i-1].first;
            int id = 0;
            while(diff){
                if(diff & 1){
                    b = lca[id][b];
                }
                diff>>=1;
                id++;
            }
            if(a != b) {
                cout << "NO\n";
                goto END;
            }
        }
        cout <<"YES\n";
        END:
        int x = 1;
    }
    return 0;
}