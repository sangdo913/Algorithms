#include<cstdio>
#include<iostream>

using namespace std;

int OddSum()
{
    int input;
    int t;

    cin >> t;
    for(int tc= 1; tc <= t; tc++)
    {
        int sum = 0;

        for(int i = 0; i < 10; i++)
        {
            cin >> input;
            sum += input & 1 ? input : 0;
        }

        cout << '#' << tc <<' ' << sum << '\n';
    }
    return 0;
}