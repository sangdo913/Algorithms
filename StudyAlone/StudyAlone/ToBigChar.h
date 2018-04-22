#include<iostream>
#include<string>

using namespace std;

int ToBigChar()
{
    string str;
    cin >> str;
    for(int i = 0 ; i < str.length(); i++)
    {
        if(str[i] >= 'a' && str[i] <='z')
        {
            str[i] -= 'a'-'A';
        }
    }

    cout << str << endl;
    return 0;
}