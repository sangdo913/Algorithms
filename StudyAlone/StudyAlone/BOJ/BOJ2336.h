#include<iostream>
#include<map>
#include<vector>
#include<algorithm>
#include<cmath>

using namespace std;
int segment[1100000];

int main(){
    ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    freopen("0Text.txt", "r", stdin);
    int n;
    cin >> n;

    vector<int> grade[2] = {vector<int>(n), vector<int>(n)};
    vector<int> p[2] = {vector<int>(n+1), vector<int>(n+1)};
    for(int i = 0; i < n*2; ++i){
        segment[i] = 0x3f3f3f3f;
    }

    for(int i = 0; i < n; ++i) cin >> grade[0][i];
    for(int i = 0; i < n; ++i) {
        cin >> grade[1][i];
        p[0][grade[1][i]] = i;
    }
    for(int i = 0; i < n;++i){
        int pos;
        cin >> pos;
        p[1][pos] = i;
    }
    int res = 0;
    for(int i = 0; i < n; ++i) {
        int g = grade[0][i];
        int p1 = p[0][g];
        int p2 = p[1][g];
        int minp1 = 0x3f3f3f3f;
        int l = n;
        int r = n + p2;
        while(l <= r){
            minp1 = min(minp1, segment[l]);
            minp1 = min(minp1, segment[r]);
            l = (l+1)/2;
            r = (r-1)/2;
        }
        if(minp1 == 0x3f3f3f3f || (minp1 > p1 || p[1][grade[1][minp1]] > p2)){
            res++;
            int idx = n + p2;
            while(idx) {
                segment[idx] = min(segment[idx], p1);
                idx /=2;
            }
        }
    }
    cout << res;

    return 0;
}