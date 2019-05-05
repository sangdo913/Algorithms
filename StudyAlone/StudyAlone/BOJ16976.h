#include<iostream>
#include<cstring>
#include<map>
#define SIZE 100001 
#define MIN(x, y) ((x) < (y) ? (x) : (y))

using namespace std;

map<int, int> mp[SIZE];
int game[SIZE];
int gamenum[SIZE];

int p[SIZE],n, m, q;
int res[SIZE];

int parent(int i){
    if(p[i] < 0 ) return i;
    return p[i] = parent(p[i]);
}

void join(int qnum, int a, int b){
    int pa = parent(a);
    int pb = parent(b);

    if(pa == pb) return;

    if(p[pa] > p[pb]){
        pa ^= pb ^= pa ^= pb;
    }

    for(auto i : mp[pb]){
        mp[pa][i.first] += i.second;
        if(mp[pa][i.first] == gamenum[i.first]) res[i.first] = qnum, mp[pa].erase(i.first);
    }

    mp[pb].clear();

    p[pa] += p[pb];
    p[pb] = pa;
}

int Do(){
    ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);

    cin >> n >> m >> q;
    memset(res, -1,sizeof(res));
    memset(p, -1, sizeof(p));

    for(int i  =1; i <= n; i++){
        cin >> game[i];
        ++gamenum[game[i]];
        mp[i][game[i]] = 1;
    }

    for(int i = 1; i <= n; i++) if(gamenum[game[i]] == 1) mp[i].erase(game[i]), res[game[i]] = 0;

    for(int i = 1; i <= q; i++){
        int a, b;
        cin >> a >> b;

        join(i, a,b);
    }

    for(int i = 1; i <= m; i++) cout << res[i] << '\n';
    return 0;
}