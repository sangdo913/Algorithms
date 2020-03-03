#include<iostream>
#define MIN(x,y) ((x) >(y) ? (y) : (x))

using namespace std;
int n,m;
struct EDGE{
    int f,t, c;
} edges[4000];
EDGE temp[4000];
int esize;
int parent[2000];
int res;

void mergesort(int s, int e){
    int l = s, m = (s+e)/2, r = m+1, k = s;
    while(l <= m && r <= e) temp[k++] = edges[l].c < edges[r].c ? edges[l++] : edges[r++];
    while(l <= m) temp[k++] = edges[l++];
    while(r <= e) temp[k++] = edges[r++];
    for(int i = s; i <= e; ++i) edges[i] = temp[i];
}

void merge(int s, int e){
    if(s<e){
        int m = (s+e)/2;
        merge(s,m);
        merge(m+1,e);
        mergesort(s,e);
    }
}

int findp(int i){
    if(parent[i] < 0) return i;
    return parent[i] = findp(parent[i]);
}

void join(int a, int b){
    int pa = findp(a), pb = findp(b);
    if(pa == pb) return;
    if(parent[pa] < parent[pb]) pa^=pb^=pa^=pb;
    parent[pb]+=parent[pa];
    parent[pa] = pb;
}

int getdiff(int s){
    for(int i = 0; i < n; ++i) parent[i] = -1; 
    int e = n-1;
    for(int i = s; i < m; ++i){
        int a = edges[i].f, b = edges[i].t; 
        int pa = findp(a), pb = findp(b);
        if(pa != pb){
            join(a, b);
        }
        if(findp(0) == findp(e)) return edges[i].c - edges[s].c;
       else if(edges[i].c - edges[s].c >= res) return 0x3f3f3f3f;
    }
    return 0x3f3f3f3f;
}

int main(){
    freopen("0Text.txt", "r", stdin);
    ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    int C;
    cin >> C;
    while(C--){
        cin >> n >> m;
        for (int i = 0; i < m; ++i)
        {
            cin >> edges[i].f >> edges[i].t >> edges[i].c;
        }
        merge(0, m - 1);
        res = 0x3f3f3f3f;
        for (int i = 0; i < m; ++i)
        {
                int temp = getdiff(i);
                res = MIN(res, temp);
        }
        cout << res << endl;
    }

    return 0;
}