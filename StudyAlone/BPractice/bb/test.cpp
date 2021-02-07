#include<iostream>
#include<algorithm>
#include<cmath>
#include<vector>

#include<cstdio>
using namespace std;

int main(){
    freopen("0Text.txt", "r", stdin);
    long long scores[2][36], n;
    vector<pair<long long,int > > score[19];
    cin >> n;
    for(int i = 0; i < n; ++i){
        cin >> scores[0][i];
    }
    for(int i = 0; i < n; ++i){
        cin >> scores[1][i];
    }
    int b = 1 << (n/2);
    for(int i = 0; i < b; ++i){
        int cnt = n/2;
        int b = i;
        long long s = 0;
        int idx = n/2-1;
        int num = 0;
        while(cnt--){
            if(b&1) {
                num++;
                s += scores[1][idx + n/2];
            }
            else {                  
                s -=  scores[0][idx+n/2];
            }
            b>>=1;
            idx--;
        }
        score[num].push_back({s,i});
    }
    for(int i = 0; i<= n/2; ++i) sort(score[i].begin(), score[i].end());
    b = 1<<(n/2);
    long long res = 0x3f3f3f3f3f3f3f3f;
    int r1, r2;
    for(int i = 0; i < b; ++i) {
        int bit=i;
        int num = 0;
        int idx = n/2-1;
        long long s = 0;
        int cnt = n/2;

        while(cnt--) {
            if(bit & 1){
                num++;
                s += scores[1][idx];
            }
            else s-=scores[0][idx];
            bit >>= 1;
            idx--;
        }
        
        idx = lower_bound(score[n/2 - num].begin(),score[n/2-num].end(), make_pair(-s,-1)) - score[n/2-num].begin();
        if(idx >= 0 && idx <  score[n/2-num].size() && res > abs(s+score[n/2-num][idx].first)){
            res = abs(s+ score[n/2-num][idx].first);
            r1 = i, r2 = score[n/2-num][idx].second;
        }
        if(idx) {
            long long  v = score[n/2-num][idx-1].first-1;
            idx = upper_bound(score[n/2-num].begin(), score[n/2-num].end(), make_pair(v,-1)) - score[n/2-num].begin();
            if(res > abs(s + score[n/2-num][idx].first)){
                res = abs(s+ score[n/2-num][idx].first);
                r1 = i, r2 = score[n/2-num][idx].second;
            }
        }
    }
    int rarr[36] = {};
    int idx = n/2-1;
    int cnt = n/2;
    while(cnt--){
        rarr[idx] = (r1&1) + 1;
        r1>>=1;
        idx--;
    }
    cnt = n/2;
    idx = n-1;
    while(cnt--){
        rarr[idx] = (r2&1) + 1;
        r2>>=1;
        idx--;
    }

    
    for(int i = 0; i < n; ++i) printf("%d ", rarr[i]);
    printf("\n");
    return 0;
}