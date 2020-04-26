#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
#include<queue>
#define MAX(x,y) ((x) > (y) ? (x) : (y))

using namespace std;
int dr[4] = {-1,1,0,0};
int dc[4] = {0,0,-1,1};
int inorder[1000000];
int to[1000000];
int visit[1000000];
int pa[1000000];
int counted[1000000];
vector<int> adj[1000000];

int main(){
    freopen("0Text.txt", "r", stdin);
    int t;
    vector<string>mv;
    vector<string> mp;
    int conv[256];
    conv['U'] = 0;
    conv['D'] = 1;
    conv['R'] = 3;
    conv['L']  = 2;
    cin >> t;
    int tc = 0;
    int query = 0;
    while(t--){
        tc++;
        int n, m;
        cin >> n >> m;
        queue<int>Q;
        mp.resize(n);
        for(int i = 0; i < n*m; ++i) adj[i].clear(), inorder[i] = 0;
        mv.resize(n);
        for(int i = 0; i < n; ++i){
            cin >> mp[i];
        }
        for(int i = 0; i < n; ++i){
            cin >>mv[i];
        }
        for(int i = 0; i < n; ++i){
            for(int j  = 0; j < m; ++j){
                int d = conv[mv[i][j]];
                int ni = i + dr[d];
                int nj = j + dc[d];
                int np = ni*m + nj;
                to[i*m + j] = np;
                adj[np].push_back(i*m+j);
                inorder[np]++;
            }
        }
        for(int i = 0; i < n*m; ++i){
            if(!inorder[i]) Q.push(i);
        }
        while(Q.size()){
            int now = Q.front(); Q.pop();
            int nn = to[now];
            
            inorder[nn]--;
            if(!inorder[nn]) Q.push(nn);
        }
        
        int res = 0, black = 0;
        for(int i = 0; i < n*m; ++i){
            if(inorder[i]){
                query++;
                res++;
                int resblack = 0;
                if(visit[i] == tc) continue;
                int p = i;
                int size = 0;
                int cursor = 0;
                while(tc != visit[p]){
                    visit[p] = tc;
                    Q.push(p);
                    pa[p] = size++; 
                    p = to[p];
                }
                while(Q.size()){
                    int cnt = Q.size();
                    int nowblack = 0;
                    while(cnt--){
                        int now = Q.front(); Q.pop();
                        if(counted[(pa[now]+cursor)%size] != query && mp[now/m][now%m] == '0'){
                            counted[(pa[now]+cursor)%size] = query;
                            resblack++;
                        }
                        for(int i  =0; i < adj[now].size(); ++i){
                            int nn = adj[now][i];
                            if(visit[nn] == tc) continue;
                            visit[nn] = tc;
                            pa[nn] = pa[now];
                            Q.push(nn);
                        }
                    }
                    cursor = (cursor - 1 + size)%size;
                }
                black += resblack;
            }
        }
        cout << res << ' ' << black << '\n';
    }

    return 0;
}