#include<iostream>

using namespace std;

bool clapNum(int n)
{
    int res = 0;
    while(n)
    {
        res += n%10 == 3 || n%10 == 6 || n%10 == 9;
        n /= 10;
    }

    for(int i = 0; i < res; i++)
    {
        cout << '-';
    } 

    return res;
}

int Simple369()
{
    int n;
    cin >> n;
    
    for(int i = 1 ; i <= n; i++)
    {
        if(clapNum(i)) cout << ' ';
        else cout << i << ' ';
    }
    return 0;
}