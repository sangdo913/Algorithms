#include<iostream>
#include<map>
#include<vector>
#include<algorithm>
#include<cmath>

using namespace std;
int segment[2100000];

int update(int i, int id, int v, int s, int e) {
    if(id < s || e <= id) return 0x3f3f3f3f;
    if(s+1 == e) return segment[i] = min(segment[i], v);
    int m = (s+e)/2;
    segment[i] = min(segment[i], update(i*2, id, v, s,m));
    segment[i] = min(segment[i], update(i*2+1, id, v, m, e));
    return segment[i];
}

int query(int i, int s, int e, int l, int r){
    if(r <= s ||e <= l) 
        return 0x3f3f3f3f;
    if(l <= s && e <= r) 
        return segment[i];
    int m = (s+e)/2;
    return min(query(i*2, s,m,l,r), query(i*2+1, m,e,l,r));
}

int main(){
    freopen("0Text.txt", "r", stdin);
    int n;
    cin >> n;
    vector<int> grade[2] = {vector<int>(n), vector<int>(n)};
    vector<int> p[2] = {vector<int>(n+1), vector<int>(n+1)};
    for(int i = 0; i < 2100000 ; ++i){
        segment[i] = 0x3f3f3f3f;
    }

    for(int i = 0; i < n; ++i) cin >> grade[0][i];
    for(int i = 0; i < n; ++i) {
        cin >> grade[1][i];
        p[0][grade[1][i]] = i;
    }
    for(int i = 0; i < n;++i){
        int pos;
        cin >> pos;
        p[1][pos] = i;
    }
    int res = 0;
    for(int i = 0; i < n; ++i) {
        int g = grade[0][i];
        int p1 = p[0][g];
        int p2 = p[1][g];
        int minp1 = query(1, 0,n, 0, p2+1);
        if(minp1 == 0x3f3f3f3f || (minp1 > p1 || p[1][grade[1][minp1]] > p2)){
            res++;
            update(1, p2, p1, 0,n);
        }
    }
    printf("%d\n", res);

    return 0;
}