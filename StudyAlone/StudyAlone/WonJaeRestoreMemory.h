#include<stdio.h>
#include<string>
#include<iostream>

using namespace std;

struct Memyro
{
    string s;
    void init()
    {
        cin >> s;
    }    

    int getMem()
    {
        char prev = '0';
        int res = 0;

        for(int i = 0; i < s.size(); i++)
        {
            if(s[i] != prev)
            {
                prev = s[i];
                res++;
            }
        }

        return res;
    }
} info;

int WonJaeRestoreMemory()
{
    int t;
    scanf("%d\n", &t);
    for(int tc = 1; tc <= t; tc++)
    {
        info.init();
        int res = info.getMem();
        printf("#%d %d\n", tc, res);
    }
    return 0;
}