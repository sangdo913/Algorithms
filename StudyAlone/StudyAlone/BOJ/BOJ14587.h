#include<iostream>
#include<cstring>
#include<vector>
#include<unordered_map>
#include<algorithm>
#define ll long long

using namespace std;

pair<ll, int> info[2000000];
int tree[2][2000000];
int dp[2000000];

int main() {
    ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    freopen("0Text.txt","r",stdin);
    int n; 
    cin >> n;
    for(int i = 0; i < n; ++i) {
        int height,pos;
        cin >> pos>> height;
        info[i] = {pos, height};
    }
    sort(info, info + n);
    int b = 1;
    while(b < n) b<<=1;

    memset(tree[0],0x3f,sizeof(tree[0]));
    memset(tree[1], -1, sizeof(tree[1]));
    int id = b;

    for(int i = 0; i <n; ++i){
        ll l = info[i].first - info[i].second;
        int f = b + (lower_bound(info, info+i, make_pair(l, -1)) - info);
        int t = b + i;
        int v = i;
        while(f <= t){
            v = min(tree[0][f], v);
            v = min(tree[0][t], v);
            f = (f+1)/2;
            t = (t-1)/2;
        }
        int id = b+i;
        while(id) {
            tree[0][id] = min(tree[0][id], v);
            id /=2;
        }
    }
    for(int i = n-1; i >= 0; --i){
        int id = b + i;
        ll r = info[i].first + info[i].second;
        int f = b + i;
        int t = b -1+ (upper_bound(info+i, info + n, make_pair(r, 0x3f3f3f3f))-info);
        int v = i;
        while(f <= t) {
            v = max(v, tree[1][f]);
            v = max(v, tree[1][t]);
            f = (f+1)/2;
            t = (t-1)/2;
        }
        id = b+i;
        while(id){
            tree[1][id] = max(tree[1][id], v);
            id/=2;
        }
    }
    memset(dp,0x3f, sizeof(dp));
    dp[0] = 1;

    for(int i = 0; i < n; ++i){
        int l = tree[0][b + i];
        dp[i] = min(dp[i], 1 + (l == 0 ? 0 : dp[l-1]));
        int r = tree[1][b+i];
        dp[r] = min(dp[r], (i == 0 ? 0 : dp[i-1]) + 1);
    }
    cout << dp[n-1];
    
    return 0;
}