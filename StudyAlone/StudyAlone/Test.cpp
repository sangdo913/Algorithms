#include<iostream>

using namespace std;
typedef int BLOCK[4];

void cpy(BLOCK a, BLOCK b)
{
    a[0] = b[0];
    a[1] = b[1];
    a[2] = b[2];
    a[3] = b[3];
}
void print(BLOCK a)
{
    cout << a[0] << ' ' << a[1] << ' ' << a[2] << ' ' << a[3] << '\n';
}
int main()
{
    BLOCK b, c;
    b[0] = 1; b[1] = 2; b[2] = 123; b[3]= 999 ;

    cpy(c, b);
    c[0] = -1;
    print(c);
    print(b);
    
    return 0;
}