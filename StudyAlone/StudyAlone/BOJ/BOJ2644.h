#include<iostream>
using namespace std;

int visit[101];
int adj[101][100];
int asize[101];
int Q[101];

int main(){
    freopen("0Text.txt", "r", stdin);
    int n;
    int s, e;
    cin >> n >> s >> e;
    int m;
    cin >> m;
    int fr, re;
    fr = re = 0;

    visit[s] = 1;
    Q[re++] = s;

    while(m--){
        int p, c;
        cin >> p >> c;
        adj[p][asize[p]++] = c;
        adj[c][asize[c]++] = p;
    }
    int len = 0;

    while(fr!=re){
        int cnt = re-fr;
        while(cnt--){
            int now = Q[fr++];
            if(now == e) return !(cout << len);
            
            for(int i = 0; i < asize[now]; ++i){
                int next = adj[now][i];
                if(visit[next]) continue;
                visit[next] = 1;
                Q[re++] = next;
            }
        }
        len++;
    }

    return !(cout << -1);
}