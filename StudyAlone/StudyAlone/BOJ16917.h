#include<iostream>

using namespace std;

int Do(){
    int a,b,c,x,y;
    cin >> a >> b >> c >> x >> y;
    a = a > 2*c ? 2*c : a;
    b = b > 2 *c ? 2*c : b;
    
    if(a + b > 2*c){
        x > y ? cout << (x-y)*a + 2*c*y : cout << (y-x)*b + 2*c*x;
    }
    else{
        cout << x*a + y*b;
    }
    return 0;
}