#include<iostream>

using namespace std;

enum TYPE{NEED, NOTNEED, CAMERA};

int ans;
int asize[1000];
int adj[1000][1000];
TYPE camera[1000];
int visit[1000];
int tc;
TYPE getcamera(int num){
    if(!asize[num]) return NEED;
    if(visit[num] == tc) return camera[num];
    visit[num] = tc;

    bool needcamera = false;
    TYPE &ret = camera[num];
    ret = NEED;
    for(int i = 0; i < asize[num]; ++i){
        int next = adj[num][i];
        if(visit[next] == tc) continue;
        TYPE res = getcamera(next);
        
        needcamera |= res == NEED;
        if(res == CAMERA) ret = NOTNEED;
    }
    if(needcamera) ans++, ret = CAMERA;
    return ret;
}

int main(){
    freopen("0Text.txt", "r", stdin);
    int c;
    scanf("%d", &c);
    for(tc = 1; tc <= c; ++tc){
        ans = 0;
        int n, m;
        cin >> n >> m;
        for(int i = 0; i < n; ++i) asize[i] = 0;
        for(int i = 0; i < m; ++i){
            int f, t;
            scanf("%d %d" , &f, &t);

            adj[f][asize[f]++] = t;
            adj[t][asize[t]++] = f;
        }
        for(int i = 0; i < n; ++i){
            if(visit[i] == tc) continue;
            TYPE res = getcamera(i);
            ans += res == NEED;
        }
        printf("%d\n", ans);
    }
    return 0;
}