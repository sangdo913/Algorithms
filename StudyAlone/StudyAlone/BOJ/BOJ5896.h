#include<iostream>
#include<queue>
using namespace std;
long long arr[50000][2];
bool isin[50000];

int main(){
    freopen("0Text.txt", "r", stdin);
    int n, k;
    long long m;
    priority_queue<long long> diff;
    priority_queue<pair<long long, int>> coupons;
    priority_queue<pair<long long, int>> ncoupons;
    cin >> n >> k >> m;

    for(int i = 0; i < n; ++i){
        cin >> arr[i][0] >> arr[i][1];
        coupons.push({-arr[i][1],i});
        ncoupons.push({-arr[i][0], i});
    }
    for(int i = 0; i < k; ++i) diff.push(0);
    int res =0;
    while(res < n && m > 0){
        while(coupons.size() && isin[coupons.top().second]) coupons.pop();
        while(ncoupons.size() && isin[ncoupons.top().second]) ncoupons.pop();
        
        long long addcouponcost = -diff.top() - coupons.top().first;
        if(addcouponcost < -ncoupons.top().first){
            int cid = coupons.top().second;
            m -= addcouponcost;
            if(m < 0) break;
            diff.pop();
            diff.push(arr[cid][1] - arr[cid][0]);
            isin[cid] = 1;
            coupons.pop();
        }
        else{
            int ncid = ncoupons.top().second;
            m-= arr[ncid][0];
            if(m < 0) break;
            isin[ncid] =1;
        }
        res++;
    }
    cout <<res;
    
    return 0;
}