#include<iostream>
#include<cstring>
#include<vector>
#include<queue>
#include<cstdio>

using namespace std;
#define MAX(x,y) ((x) > (y) ? (x) : (y))
#define MIN(x,y) ((x) < (y) ? (x) : (y))

int check[5001][5001];
int getmin[5001];
int getmax[5001];
int parent[5001];
int nodenum;

void make(int p, int n, int d){
    if(n ==0) return;
    int now = ++nodenum;
    parent[now] = p;
    d-=n-1;
    for(int i = 0; i < n; ++i){
        int r = n-1-i;
        int drmin = d - getmax[i];
        int drmax = d - getmin[i];
        if(drmax < getmin[r] || getmax[r] < drmin) continue;
        if(drmin < getmin[r]) drmin = getmin[r];
        if(drmin < 0 ) drmin = 0;
        make(now, i,d - drmin);
        make(now, r,drmin);
        return;
    }
}


int main(){
    // freopen("0Text.txt", "r", stdin);
    int tc;
    cin >> tc;
    getmin[1] = 0;
    for(int i = 2; i <= 5000; ++i){
        int j = (1<<i)-1;
        if(j > 5000) break;
        getmin[j] = getmin[(1<<(i-1))-1] + (1<<(i-1))*(i-1);
    }
    for(int i =2; i <= 5000; ++i){
        int bs = 20;
        while(bs &&!((1 << bs) & (i+1))) --bs;
        int nnum = (1<<bs) -1;
        getmin[i] = getmin[nnum] + bs*(i-nnum);
        getmax[i] = (i-1)*i/2;
    }
    while(tc--){
        nodenum = 0;

        int n , d;
        cin >> n >> d;

        if(getmin[n] <= d && d <= getmax[n]){
            cout << "YES\n";
            make(0,n,d);
            for(int i =2; i <=n; ++i){
                cout << parent[i] << ' ';
            }
            cout << endl;
        }
        else cout << "NO\n";
    }
    return 0;
}