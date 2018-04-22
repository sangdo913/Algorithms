#include<iostream>

using namespace std;

int PatternLength()
{
    char str[31];
    char pattern[31];
    int t;
    cin >> t;
    int plen;
    for(int tc = 1; tc <= t; tc++)
    {
        scanf("%s\n", str);
        for(int i = 1; i < 30; i++)
        {
            bool isPattern = true;
            for(int j = 0; j < i; j++)
            {
                pattern[j] = str[j];
            }

            for(int j = 0; j < 30 && isPattern; j++)
            {
                isPattern &= str[j] == str[j%i];
            }
            plen = i;
            if(isPattern) break;
        }
        cout << '#' << tc << ' ' << plen << '\n';
    }
    return 0;
}