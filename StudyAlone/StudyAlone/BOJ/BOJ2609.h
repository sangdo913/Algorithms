#include<iostream>

using namespace std;

int main(){
    freopen("0Text.txt", "r", stdin);
    int a, b;
    cin >> a >> b;
    int mul = a*b;

    if(a <b) a^=b^=a^=b;
    int r = a%b;
    while(r){
        a = b;
        b = r;
        r = a%b;
    }
    return !(cout << b << '\n' << mul/b);
}