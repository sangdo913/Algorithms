#include<iostream>
#include<cmath>

using namespace std;
struct EDGE{
    int a, b;
    double c;
};
EDGE edges[250000];
EDGE temp[250000];
void merge(int s, int e){
    int l = s, m = (s+e)/2, r = m + 1, k  =l;
    while(l <= m && r <= e){
        temp[k++] = edges[l].c < edges[r].c ? edges[l++] : edges[r++];
    }
    while(l<=m) temp[k++] = edges[l++];
    while(r <= e) temp[k++] = edges[r++];
    for(int i = s; i <= e; ++i) edges[i] = temp[i];
}
int parent[500];

void mergesort(int s, int e){
    if(s < e){
        int m = (s+e)/2;
        mergesort(s,m);
        mergesort(m+1,e);
        merge(s,e);
    }
}

int coord[2][500];

#define DIST(a,b) (((a)-(b))*((a)-(b)))

int findp(int i){
    if(parent[i] < 0) return i;
    return parent[i] = findp(parent[i]);
}

void join(int a, int b){
    int pa = findp(a), pb = findp(b);

    if(pa == pb) return;
    if(parent[pa] < parent[pb]) pa^=pb^=pa^=pb;

    parent[pb] += parent[pa];
    parent[pa] = pb;
}

int main(){
    freopen("0Text.txt", "r", stdin);
    ios_base::sync_with_stdio(0), cout.tie(0), cin.tie(0);
    int C;
    cin >> C;
    cout.setf(ios_base::fixed);
    cout.precision(10);
    while(C--){
        int n,m;
        cin >> n >> m;
        for(int i = 0; i < n; ++i){
            cin >> coord[0][i];
            parent[i] = -1;
        }
        for(int i = 0; i < n; ++i){
            cin >> coord[1][i];
        }
        int esize = 0;
        while(m--){
            int a, b;
            cin >> a >> b;
            join(a,b);
        }
        for(int i = 0; i < n; ++i){
            for(int j = i+1; j < n; ++j){
                int pa = findp(i), pb = findp(j);
                if(pa == pb) continue;
                edges[esize].a = i;
                edges[esize].b = j;
                edges[esize++].c = sqrt((double)DIST(coord[0][i], coord[0][j]) + DIST(coord[1][i], coord[1][j]));
            }
        }
        mergesort(0, esize-1);
        double res = 0;

        for(int i = 0; i < esize;++i){
            int pa = findp(edges[i].a), pb = findp(edges[i].b);
            if(pa == pb) continue;
            res += edges[i].c;
            join(edges[i].a, edges[i].b);
        }
        cout << res << '\n';
    }
    return 0;
}