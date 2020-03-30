#include<iostream>
#include<vector>
#include<algorithm>
#define MIN(x,y) ((x) > (y) ? (y) : (x))

using namespace std;
vector<pair<int, int>> vec[40001];
int arr[40001];
int n,m;
int dp[40001];

void getdp(int i){
    if(i == n) return;
    for(int j = 0; j < vec[i].size(); ++j){
        int ni = vec[i][j].first;
        dp[ni] = MIN(dp[ni], dp[i] + vec[i][j].second);
    }
    getdp(i+1);
}

int main(){
    freopen("0Text.txt", "r", stdin);
    cin >> n >> m;
    for(int i = 0; i < n; ++i){
        cin >> arr[i];
        dp[i] = 0x3f3f3f3f;
    }
    int ii = 1;
    
    while(ii*ii < n){
        vector<int> cnt(n, 0);
        int samenum = 0;
        int j =0;
        for(int i = 0; i < n; ++i){
            while(j < n && samenum < ii ||(samenum == ii && cnt[arr[j]])){
                if(cnt[arr[j]]++ == 0) samenum++;
                ++j;
            }

            if(j - i >= ii*ii) vec[i].push_back({j, ii*ii});
            cnt[arr[i]]--;
            if(!cnt[arr[i]]) samenum--;
        }
        ++ii;
    }
    // for(int i = 0; i < n; ++i){
    //     cout <<"=================\n";
    //     cout << i << endl;
    //     for(int j = 0; j < vec[i].size(); ++j){
    //         cout << vec[i][j].first << ' ' << vec[i][j].second << '|';
    //     }
    //     cout << endl;
    // }
    dp[0] = 0;
    dp[n] = 0x3f3f3f3f;
    for(int i = 0; i < n; ++i){
        for(int j = 0; j < vec[i].size(); ++j){
            int ni = vec[i][j].first;
            dp[ni] = MIN(dp[i] + vec[i][j].second, dp[ni]);
        }
    }
    cout << dp[n];

    return 0;
}