#include<iostream>

using namespace std;

int main(){
    freopen("0Text.txt", "r", stdin);
    int n;
    cin >> n;
    while(n--){
        int m;
        cin >> m;
        cout << (m/2 - ((m&1) == 0)) << '\n';
    }


    return 0;
}