#include<iostream>
#include<map>
#include<algorithm>
#include<vector>
#include<set>
#include<stdio.h>
#define M 10007

using namespace std;

int n;
map<long long, vector<int>> mp; 
set<int> se;
vector<int> vec;
long long v[1<<20];
int check[M];
int arr[20];

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
        mp[sum].push_back(i);
    }
    for(auto it : mp){
        auto v = it.second;
        sort(v.begin(), v.end());
    }

    int res = 0;
    for(int i = 1; i < (1<<n); ++i){
        int b= i;
        int val = v[i];
        if(val &1) continue;
        val >>=1;
        auto vec = mp[val];
        int idx = lower_bound(vec.begin(), vec.end(), i) - vec.begin();
        if(idx){
            printf("0x : %0x\n", i);
            cout << val << endl;
            res++;
        }
    }

    cout << res;
    return 0;
}