#include<iostream>
#include<map>
#include<algorithm>
#include<vector>
#include<set>
#include<stdio.h>
#define M 10007

using namespace std;

int n;
map<long long, vector<int>> f, myback; 
set<int> se;
vector<int> vec;
long long v[1<<20];
long long diff[1<<20];
int check[1<<20];
int arr[20];
#define ABS(x) ((x) > 0 ? (x) : -(x))

int main(){
    int bits[M] = {};
    for(int i = 0; i < 20; ++i){
        bits[(1<<i)%M] = i;
    }
    freopen("0Text.txt", "r", stdin);

    cin >> n;
    for(int i = 0; i < n; ++i) cin >>arr[i];
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

    f[0].push_back(0);
    int m = (n/2) + (n&1);
    for(int i = 0; i < (1<<m); ++i){
        for(int j = i; j; j = (j-1)&i){
            f[ABS(v[i^j]-v[j])].push_back(i);
        }
    }

    for(int i = 0; i < (1<<(n-m)); ++i){
        int b = i<<m;
        for(int j = b; j ; j = (j-1)&b){
            myback[ABS(v[b^j]-v[j])].push_back(b);
        }
    }
    int res = 0;
    check[0] = 1;
    myback[0].push_back(0);
    for(auto it : f){
        int diff = it.first;
        vector<int> &vec = it.second;
        vector<int> &vec2 = myback[diff];
        for(auto it : vec){
            for(auto it2 : vec2){
                if(!check[it | it2]){
                    // cout << (it|it2) << endl;
                    check[it|it2] = 1;
                    res++;
                }
            }
        }
    }

    cout << res;
    return 0;
}