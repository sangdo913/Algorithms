#include<iostream>

using namespace std;

int GetBiggest()
{
    int t;
    cin >> t;
    for(int tc = 1; tc <= t; tc++)
    {
        int max = 0, input;
        for(int i = 0; i < 10; i++)
        {
            cin >> input;
            max = max < input ? input : max;
        }

        cout << '#' << tc << ' ' << max << '\n';
    }
    return 0;
}