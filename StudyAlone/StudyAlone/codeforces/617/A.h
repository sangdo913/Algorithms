#include<iostream>

using namespace std;
int arr[2000];

int main(){
    freopen("0Text.txt", "r", stdin);
    int tc;
    cin >> tc;
    while(tc--){
        int n;
        cin >> n;
        bool possible = false;
        bool isodd = false;
        for(int i = 0; i < n; ++i) {
            cin >> arr[i];
            if(!(arr[i] &1)) possible = true;
            if(arr[i] & 1) isodd = true;
        }
        if(possible && isodd) cout << "YES\n";
        else if(isodd && (n&1)) cout << "YES\n";
        else cout << "NO\n";
    }

    return 0;
}