#include<iostream>

using namespace std;

int AVGNums()
{
    int input;
    int t;
    cin >> t;
    for(int tc = 1; tc <= t; tc++)
    {
        int sum = 0;
        for(int i = 0; i < 10; i++)
        {
            cin >> input;
            sum += input;
        }

        cout << '#' << tc << ' ' << (sum + 5) / 10 << '\n';
    }
}