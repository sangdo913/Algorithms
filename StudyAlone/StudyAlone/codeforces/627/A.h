#include<iostream>

using namespace std;

int main(){
    freopen("0Text.txt","r", stdin);
    int tc;
    cin >> tc;
    while(tc--){
        int n;
        int x;
        cin >> n;
        cin >> x;

        int type = x%2;
        bool res = true;
        for(int i = 1; i < n; ++i){
            cin >> x;
            int t = x%2;
            if(type != t){
                res =false;
            }
        }
        if(res) cout << "YES\n";
        else cout << "NO\n";
    }
    return 0;
}