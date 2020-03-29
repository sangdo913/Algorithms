#include<iostream>
#include<algorithm>
#include<vector>
#define ABS(x) ((x) > 0 ? (x) : -(x))

using namespace std;

long long dp[5001];
long long value[5001][5001];
int minm[5001];
long long sum[5001];
vector<int> l;
int c, m;
int n;

long long getres(int i){
    long long &ret = dp[i];
    if(ret != -1) return ret;
    ret = value[i][n] + m;
    minm[i] = 1;

    for(int j = i +1; j <= n; ++j){
        long long res = value[i][j-1] + m + getres(j);
        int mres = minm[j] + 1;
        if(res < ret){
            ret = res;
            minm[i] = mres;
        }
        else if(ret == res && mres < minm[i]){
                minm[i] = mres;
        }
    }
    return ret;
}

int main(){
    freopen("0Text.txt", "r", stdin);
    cin >> n;
    l.resize(n+1);
    for(int i = 1; i <= n; ++i) {
        cin >> l[i];
    }
    cin >> c >> m;
    sort(l.begin()+1, l.end());

    n = l.size()-1;
    for(int i = 1; i<= n; ++i){
        sum[i] = sum[i-1] + l[i];
    }
    for(int i = 1; i <= n; ++i){
        for(int j = i; j <= n; ++j){
            int l = (i+j)/2;
            if((j-i+1) & 1){
                value[i][j] = c*(sum[j]-sum[l] - (sum[l-1] - sum[i-1]));
            }
            else{
                value[i][j] = c*(sum[j] - sum[l] - (sum[l]- sum[i-1]));
            }
        }
    }
    for(int i = 1; i <= n; ++i) dp[i] = -1;
    cout << getres(1) << ' ' << minm[1];

    return 0;
}