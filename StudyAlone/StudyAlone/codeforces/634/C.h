#include<iostream>
#include<algorithm>
#include<vector>

using namespace std;
int cnt[200001];

int main(){
    freopen("0Text.txt", "r", stdin);
    int t;
    cin >> t;

    while(t--){
        vector<int> arr;
        int mmax = 0;
        int n;
        cin >> n;
        for(int i = 1; i <=n; ++i) cnt[i] = 0;
        for(int i = 0; i < n; ++i) {
            int a;
            cin >> a;
            arr.push_back(a);
            cnt[a]++;
            if(mmax < cnt[a]) mmax = cnt[a];
        }
        sort(arr.begin(), arr.end());
        int num = unique(arr.begin(), arr.end()) - arr.begin();
        if(num >= mmax) num--;
        cout << (num < mmax ? num : mmax) << '\n';
    }
    return 0;
}