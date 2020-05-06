#include<iostream>
#define MAX(x,y) ((x) > (y) ? (x) : (y))
#include<cstring>
#define HSIZE 10007
#define MAX(x,y) ((x) > (y) ? (x) : (y))
using namespace std;

long long sum[249];
int dp[248][248];
int arr[248];
int getdp(int s, int e){
    if(s == e){
        return arr[s];
    }
    int &ret = dp[s][e];
    if(ret != -1) return ret;
    ret = 0;
    for(int i = s; i < e; ++i){
        int r1 = getdp(s,i);
        int r2 = getdp(i+1, e);
        if(r1 != 0 && r1 == r2){
            ret = r1+1;
        }
    }
    return ret;
}
int mhash[HSIZE];

int main(){
    freopen("0Text.txt", "r", stdin);
    int n;
    cin >> n;
    memset(dp,-1,sizeof(dp));
    for(int i = 0; i < n; ++i) cin >> arr[i];
    getdp(0,n);
    int res = 0;
    for(int i = 0; i < n; ++i){
        for(int j = i; j < n; ++j){
            if(res < dp[i][j]) res = dp[i][j];
        }
    }
    cout << res;
    return 0;
}