#include<iostream>
#include<algorithm>
#include<vector>
#define MIN(x,y) ((x) > (y) ? (y) : (x))
using namespace std;
#define ll long long

int X[200001];
int V[200001];
int xi[200001];
long long sums[200001];
int n;

struct cmp{
    bool operator()(int a, int b){
        return X[a] < X[b];
    }
};

int temp[200001];
long long merge(int s, int e){
    int l = s, m = (s+e)/2, r = m+1, k = l;
    long long res = 0;
    while(l <= m && r <= e){
        if(V[xi[l]] > V[xi[r]]){
            int b = m;
            res += (ll)(m-l+1)*X[xi[r]];
            while(b){
                res -= sums[b]; 
                b -= b&-b;
            }
            b = l-1;
            while(b){
                res += sums[b];
                b -= b&-b;
            }
            temp[k++] = xi[r++];
        }
        else{
            temp[k++] = xi[l++];
        }
    }
    while(l <=m) temp[k++] = xi[l++];
    while(r <= e) temp[k++] = xi[r++];
    for(int i = s; i <= e; ++i){
        int diff = X[temp[i]]- X[xi[i]];
        int b = i;
        while(b <= n) {
            sums[b] += diff;
            b += b&-b;
        }
        xi[i] = temp[i];
    }
    return res;
}
long long mergesort(int s, int e){
    long long res = 0;
    if(s<e){
        int m = (s+e)/2;
        res = mergesort(s,m);
        res += mergesort(m+1,e);
        res += merge(s,e);
    }
    return res;
}
int main(){
    freopen("0Text.txt", "r", stdin);
    cin >> n;
    for(int i = 1; i <= n; ++i){
        xi[i] = i;
        cin >> X[i];
    }
    for(int i = 1; i <= n; ++i){
        cin >> V[i];
    }
    sort(xi+1, xi+n+1, cmp());
    long long res = 0;
    for(int i = 1; i <= n; ++i){
        int b = i;
        while(b <= n){
            sums[b] += X[xi[i]];
            b+= b&-b;
        }
    }
    for(int i = 1; i <= n; ++i){
        res += (long long)(i-1)*X[xi[i]];
        int b = i-1;
        while(b){
            res -= sums[b];
            b-=b&-b;
        }
    }
    cout << res - mergesort(1,n);
    return 0;
}