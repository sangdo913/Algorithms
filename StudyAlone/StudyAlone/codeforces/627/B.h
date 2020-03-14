#include<iostream>

using namespace std;

int check[5001];
int pos[5001];
int main(){
    freopen("0Text.txt", "r", stdin);
    int t;
    cin >> t;
    for(int tc= 1; tc <= t; ++tc) {
        int n;
        cin >> n;
        bool res = true;
        int x;
        cin >> x;
        for(int i = 1 ; i <= n; ++i) pos[i] = 0x3f3f3f3f;
        pos[x] = 0;
        check[x] = tc;
        cin >> x;
        if(pos[x] > 1) pos[x] = 1;
        check[x] = tc;
        for(int i = 2; i < n; ++i){
            cin >> x;
            if(check[x] == tc && pos[x] +1 != i ) {
                // cout <<pos[x] << ' '<< i << ' ';
                res = false;
            }
            check[x] = tc;
            if(pos[x] > i)  pos[x] = i;
        }
        // cout <<'\n';
        if(res) cout << "NO\n";
        else cout <<"YES\n";
    }
    return 0;
}