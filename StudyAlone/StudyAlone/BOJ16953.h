#include<iostream>

using namespace std;

int Do(){
    int a ,b;
    cin >> a >> b;
    int cnt= 1;
    while(b >= a){
        if(a == b) return !(cout << cnt);
        if(b %10 ==  1){
            b/=10;
        }
        else if(b %2 == 0){
            b>>=1;
        }
        else return! (cout << -1);
        cnt++;
    }
    cout << -1;
    return 0;
}