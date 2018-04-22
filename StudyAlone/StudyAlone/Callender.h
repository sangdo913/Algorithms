#include<iostream>

using namespace std;

int getNum(char *str)
{
    return str[1] - '0' + (str[0] - '0') * 10;
}

int Callender()
{
    int t;
    char callender[9];
    const int day[13] = {-1, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    cin >> t;
    for(int tc = 1; tc <= t; tc++)
    {
        cin >> callender;
        int month = getNum(callender + 4);
        int days = getNum(callender + 6);
        if(days > day[month] || days < 1) cout <<'#' << tc << ' ' << -1 << endl;
        else
        {
            cout << '#' << tc << ' ';
            for(int i = 0 ; i < 4; i++)
            {
                cout << callender[i];
            }
            cout <<'/';
            cout << callender[4] << callender[5];
            cout << '/';
            cout << callender[6] << callender[7];
            cout << endl;
        }
        
    }
}