#include<iostream>

using namespace std;

int ResumMoney()
{
    const int money[8] = {50000, 10000, 5000, 1000, 500, 100, 50, 10};

    int t;
    cin >> t;

    for(int tc = 1; tc <= t; tc++)
    {
        int n; 
        cin >> n;
        cout << '#' << tc << '\n';
        for(int i = 0; i < 8; i++)
        {
            cout << n / money[i] << ' ';
            n %= money[i];
        }
        cout << '\n';
    }
    return 0;
}