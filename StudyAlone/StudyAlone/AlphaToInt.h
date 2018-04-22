#include<iostream>
#include<string>

using namespace std;

int AlphaToInt()
{
    string str;
    cin >> str;
    for(int i = 0; i < str.length(); i++)
    {
        cout << str[i] - 'A' + 1 << ' ' ;
    }
    cout << endl;
    return 0;
}