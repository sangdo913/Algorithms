//Sleeping Schedule
#include<iostream>

using namespace std;
int dp[2000][2000];
int vsleep[2000];
int n,h,l,r;

int goodtime(int a, int hour){
    if(a == n) return 0;
    int &ret = dp[a][hour];
    if(ret != -1) return ret;
    ret = 0;
    int nh = (hour + vsleep[a]) %h;
    ret = goodtime(a +1, nh) + (l <= nh && nh <= r);
    nh = (h+nh-1)%h;
    int t = goodtime(a+1,nh) + (l <= nh && nh <= r);
    if(ret < t) ret = t;
    return ret;
}

int main(){
    freopen("0Text.txt", "r", stdin);
    cin >> n >> h >> l >> r;
    for(int i = 0; i < n; ++i) cin >> vsleep[i];
    for(int i = 0; i < n; ++i){
        for(int j = 0; j < h; ++j)
        dp[i][j] = -1;
    }

    return !(cout << (goodtime(0,0) + (l == 0)));
}