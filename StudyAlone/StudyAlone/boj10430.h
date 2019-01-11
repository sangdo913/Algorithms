#include<iostream>

using namespace std;

int Do(){
    int a, b, c;
    cin >> a >> b >> c;
    int a1 = (a+b)%c, a2 = (a*b)%c;
    cout << a1 << '\n' << a1 << '\n' << a2 << '\n' << a2;
    return 0;
}