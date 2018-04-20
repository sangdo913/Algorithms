#include<iostream>

using namespace std;

int BiggerSameLower()
{
    int t;
    cin >> t;

    for(int tc = 1; tc <= t; tc++)
    {
        int in1, in2;
        cin >> in1 >> in2;
        cout<< '#' << tc << ' ' ;
        if(in1 > in2) cout << '>';
        else if (in1 == in2) cout << '=';
        else cout << '<';
        cout << '\n';
    }
    return 0;
}