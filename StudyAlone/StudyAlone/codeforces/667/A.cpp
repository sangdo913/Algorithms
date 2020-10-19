#include<iostream>
#include<algorithm>
#include<cmath>
using namespace std;

int main(){
    freopen("0Text.txt", "r", stdin);
    int k;
    cin >> k;
    while(k--){
        int a, b;
        cin >> a >> b;
        cout << abs(b-a)/10 + (bool)(abs(b-a)%10) << endl;
    }
    return 0;
}