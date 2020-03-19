#include<iostream>
#include <algorithm>
#define MOD 10007

using namespace std;

pair<unsigned long long, int> myhash[100002];
int num[30];
int bits[MOD];

int main(){
    freopen("0Text.txt", "r", stdin);
    int n,k;
    
    cin >> n >> k;
    for(int i = 0; i < k; ++i) bits[(1<<i)%MOD] = i;
    
    int x;
    myhash[0] = {0,0};
    for(int i = 1;i <= n;++i){
        cin >> x;

        while(x){
            int b = x&-x;
            num[bits[b%MOD]]++;
            x -= b;
        }
        
        int mmin = num[0];
        
        for(int j = 1;j < k;++j)
            if(mmin > num[j]) mmin = num[j];
        
        for(int j = 0;j < k;++j)
            num[j] -= mmin;
        
        unsigned long long key = 0;

        for(int j = 0; j < k;++j) key = key * 100007 + num[j];
        myhash[i] = {key, i};
    }
    
    sort(myhash, myhash + n+1);
    
    int res = 0;
    for(int i = 0; i <= n; ){
        int j = i;
        while(j <= n && myhash[i].first == myhash[j].first) ++j;
        int diff = myhash[j-1].second - myhash[i].second;
        if(res < diff){
            res = diff;
        }
        i = j;
    }
    
    cout << res;
    
    return 0;
}