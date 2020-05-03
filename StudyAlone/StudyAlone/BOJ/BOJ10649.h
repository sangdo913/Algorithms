#include<iostream>
#include<cstring>

using namespace std;
int dp[1<<20];

int info[20][3];
int n,h;
#define HSIZE 10007
#define MIN(x,y) ((x) > (y) ? (y) : (x))
#define MAX(x,y) ((x) > (y) ? (x) : (y))
enum INFO {L, W, F};

int getdp(int visit, int t, long long w){
    if(dp[visit] != -1) return dp[visit];
    if(t >= h){
        return 0x3f3f3f3f;
    }
    int &ret = dp[visit];
    ret = -2;
    for(int i = 0;  i< n; ++i){
        if(visit & (1<<i)) continue;
        if(info[i][F] < w) continue;
        if(w > 1000000000) continue;
        int res = getdp(visit | (1<<i), t + info[i][L], w + info[i][W]);
        if(res == -2) continue;
        res = MIN(res, info[i][F] - w);
        ret = MAX(ret,res);
    }
    return ret;
}

int main(){
    memset(dp, -1, sizeof(dp));
    freopen("0Text.txt", "r", stdin);
    cin >> n >> h;
    for(int i = 0; i < n; ++i){
        cin >> info[i][0] >> info[i][1] >> info[i][2];
    }
    int ret = getdp(0,0,0);
    if(ret == -2) cout <<"Mark is too tall\n";
    else cout << ret <<'\n';

    return 0;
}