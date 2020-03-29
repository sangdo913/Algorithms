#include<iostream>

using namespace std;

int main(){
    freopen("0Text.txt", "r", stdin);
    int n;
    cin >> n;
    while(n--){
        int a, b;
        cin >> a >> b;
        cout << (b-a%b)%b << endl;
    }
    return 0;
}