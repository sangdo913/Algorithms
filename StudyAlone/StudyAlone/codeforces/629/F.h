#include<iostream>
#define MIN(x,y) ((x) > (y) ? (y) : (x))
#include<algorithm>
#include<vector>

using namespace std;
vector<int> vec;
int n, k;

int main(){
    freopen("0Text.txt", "r", stdin);
    int n, k;
    cin >> n >> k;
    for(int i = 0; i < n; ++i) {
        int a;
        cin >> a;
        vec.push_back(a);
    }
    sort(vec.begin(),vec.end());
    vector<int> compress =vec;
    compress.resize(unique(compress.begin(), compress.end()) - compress.begin());
    int p = compress[0];
    if(compress.size() == 1) {
        cout << 0;
        return 0;
    }
    int rr = upper_bound(vec.begin(), vec.end(), compress[1]) -vec.begin();
    int rl = lower_bound(vec.begin(), vec.end(), compress[1]) - vec.begin();
    
    int lr =  0;
    int ll =  0;

    long long cnt = 0;
    long long cnt1 = 0;
    for(int i = rl; i < n; ++i){
        cnt += vec[i] - p-1;
    }
    int equal = rl - lr;
    long long res =0;
    if(equal < k){
        res = cnt + k-equal;
    }
    else res = 0;

    for(int i = 1; i < compress.size()-1; ++i){
        int p = compress[i-1];
        int now = compress[i];
        cnt1 += (long long)(rl - lr)*(now-1-p);
        cnt1 += (long long)lr*(now-p);
        cnt -= (long long)(now - (p+1)) * (rr-rl);
        cnt -= (long long)(now - p)*(n - rr);
        
        rr = upper_bound(vec.begin(), vec.end(), compress[i+1]) -vec.begin();
        rl = lower_bound(vec.begin(), vec.end(), compress[i+1]) - vec.begin();
        
        lr = upper_bound(vec.begin(), vec.end(), p) -vec.begin();
        ll = lower_bound(vec.begin(), vec.end(), p) - vec.begin();
        if(rl - lr < k) {
            equal = k-rl + lr;
            res = MIN(res, (long long)equal + cnt + cnt1);
            if(equal <= n-rl)
                res = MIN(res, equal + cnt);
            if(equal <= lr)
                res = MIN(res, equal + cnt1);
        }
        else{
            res = 0;
        }
    }
    p = compress[compress.size()-2];
    int now = compress[compress.size()-1];
    cnt1 += (long long)(rl - lr)*(now-1-p);
    cnt1 += (long long)lr*(now-p);
    cnt -= (long long)(now - (p+1)) * (rr-rl);
    cnt -= (long long)(now - p)*(n - rr);
    int l = lower_bound(vec.begin(), vec.end(), now) - vec.begin();
    int r = upper_bound(vec.begin(), vec.end(), now) - vec.begin();
    if(r - l < k){
        equal = k-r + l;
        res = MIN(res, equal + cnt + cnt1);
        if(equal <= n-r)
            res = MIN(res, equal + cnt);
        if(equal <= l)
            res = MIN(res, equal + cnt1);
    }
    else res = 0;
    
    cout<< res;
    
    return 0;
}