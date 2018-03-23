#include<iostream>
using namespace std;


inline int isHansoo(int i)
{
    bool result = 0;
    int diff = i%10;
    int prev;
    i /= 10;
    prev = i%10;
    diff -= prev;
    i/=10;
    while(i)
    {
        if(prev- (i%10) != diff) return 0;

        i/=10;
    }
    return 1;
}

int HanSoo()
{
    int now = 0;
    int n;
    cin >> n;
    
    for(int i = 1; i <= n;i++)
    {
        now += isHansoo(i);
    }
    cout << now << '\n';
    return 0;
}