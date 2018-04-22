#include<iostream>


using namespace std;

int sumPositionNum()
{
    int n;
    cin >> n;
    int res = 0;
    while(n)
    {
        res += n % 10;
        n /= 10;
    }

    cout << res << '\n';
    return 0;
}