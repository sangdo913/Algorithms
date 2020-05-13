#include<iostream>

using namespace std;
int q[40000][4];
int maxarr[201];
int minarr[201];
int mmin[201], mmax[201];
int arr[201];
int visit[201];
int a[201];
int query;
int b[201];
int n,m;

#define MIN(x,y) ((x) > (y) ? (y) : (x))
#define MAX(x,y) ((x) < (y) ? (y) : (x))

bool biperate(int i){
    int f = minarr[i];
    int t = maxarr[i];
    if(visit[i] == query) return false;
    visit[i] = query;
    for(int j = f; j <= t; ++j){
        if(i < mmin[j] || mmax[j] < i) continue;
        if(b[j] == -1 || biperate(b[j])) {
            a[i] = j;
            b[j] = i;
            return true;
        }
    }
    return false;
}

int main(){
    freopen("0Text.txt", "r", stdin);
    cin >> n >> m;
    for(int i = 1; i <= n; ++i) mmin[i] = 1, mmax[i] = n,maxarr[i] = n, minarr[i] = 1, b[i] = -1;
    
    int comm, f, t, v;
    for(int i = 0; i < m; ++i){
        cin >> comm >> f >> t >> v;
        if(t < minarr[v] || maxarr[v] < f) goto FAIL;
        minarr[v] = MAX(f,minarr[v]);
        maxarr[v] = MIN(t, maxarr[v]);
        for(int j = f;  j <= t; ++j){
            if(comm == 1){
                mmax[j] = MIN(mmax[j],v);
            }
            else{
                mmin[j] = MAX(mmin[j],v);
            }
        }
    }

    for(int i = 1; i <= n; ++i){ 
        query++;
        if(!biperate(i)) goto FAIL;
    }
    for(int i =1; i <= n; ++i) cout << b[i] << ' ' ;

    return 0;

    FAIL:
    cout << -1;
    
    return 0;
}