#include<iostream>
#include<map>
#include<algorithm>
#include<vector>
#include<set>
#include<stdio.h>
#include<stdlib.h>
#define M 10007

using namespace std;

int n;
vector<pair<int,int>> f,myback;
long long v[1<<20];
int check[1<<20];
int arr[20];
#define ABS(x) ((x) > 0 ? (x) : -(x))

int main(){
    int bits[M] = {};
    for(int i = 0; i < 20; ++i){
        bits[(1<<i)%M] = i;
    }
    // freopen("0Text.txt", "r", stdin);

    n = 20;
    for(int i  =0; i < n; ++i) arr[i] = rand()%100;
    // cin >> 20;
    // for(int i = 0; i < n; ++i) cin >>arr[i];
    for(int i = 1; i < (1<<n); ++i){
        int b = i;
        long long sum = 0;

        while(b){
            int bit = b & -b;
            sum += arr[bits[bit%M]];
            b -= b&-b;
        }
        v[i] = sum;
    }

    f.push_back({0,0});
    int m = (n/2) + (n&1);
    for(int i = 0; i < (1<<m); ++i){
        for(int j = i; j; j = (j-1)&i){
            f.push_back({ABS(v[i^j]-v[j]), i});
        }
    }

    for(int i = 0; i < (1<<(n-m)); ++i){
        int b = i<<m;
        for(int j = b; j ; j = (j-1)&b){
            myback.push_back({ABS(v[b^j]-v[j]),b});
        }
    }
    int res = 0;
    check[0] = 1;
    myback.push_back({0,0});
    sort(f.begin(),f.end());
    sort(myback.begin(),myback.end());
    f.resize(unique(f.begin(),f.end()) - f.begin());
    myback.resize(unique(myback.begin(),myback.end())-myback.begin());
    int p=0,q=0,p1,q1;
    while(p<f.size() || q < myback.size()){
        if(p < f.size() && f[p].first < myback[q].first) ++p;
        else if(q < myback.size() && myback[q].first < f[p].first) ++q;
        else{
            p1 = p, q1 = q;
            while(p1 < f.size() && f[p].first == f[p1].first) p1++;
            while(q1 < myback.size() && myback[q].first == myback[q1].first) q1++;
            for(int i = p; i < p1; ++i){
                for(int j = q; j < q1; ++j){
                    if(!check[f[i].second | myback[j].second]){
                        res++;
                        check[f[i].second | myback[j].second] = 1;
                    }
                }
            }
            p = p1;
            q = q1;
        }
    }
    cout <<f.size() << ' ' << myback.size() << endl;

    cout << res;
    return 0;
}