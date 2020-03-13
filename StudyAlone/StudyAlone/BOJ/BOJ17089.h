#include<iostream>

using namespace std;

int visit[4001];
int Q[4000];
int adj[4001][4000];
int p[4001];
int alen[4001];

int main(){
    freopen("0Text.txt", "r", stdin);
    int n, m;
    cin >> n>> m;
    while(m--){
        int f, t;
        cin >> f >> t;
        adj[f][alen[f]++] = t;
        adj[t][alen[t]++] = f;
    }
    int res = 0x3f3f3f3f;
    for(int ii =1; ii <= n; ++ii){
        visit[ii] = 4000*ii+1;
        int fr =0, re = 0;
        Q[re++] = ii;
        
        int cnt = 2;
        while(cnt--){
            int remain = re - fr;
            while(remain--){
                int now = Q[fr++];
                for(int i = 0; i < alen[now]; ++i){
                    int next = adj[now][i];
                    if(visit[now] == visit[next]) {
                        int candi = alen[now] + alen[next] + alen[p[now]] - 6;
                        if(candi < res) res = candi;
                    }
                    if(visit[next] <= 4000*ii){
                        p[next] = now;
                        visit[next] = visit[now]+1;
                        Q[re++] = next;
                    }
                }
            }
        }
    }

    return !(cout << (res == 0x3f3f3f3f ? -1 : res));
}