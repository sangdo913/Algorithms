#include<iostream>
#include<cstring>

using namespace std;

struct Infos
{
    int m,n;
    int prev[2];
    int res;
    
    void init()
    {
        cin >> m  >> n;
        prev[0] = n; prev[1] = m-1;
        int index = 0;
        res = 0;
        while(prev[index^1])
        {
            res++;
            prev[index]--;
            index ^= 1;
        }
    }
} info;


int DalPang2()
{
    info.init();
    cout << info.res << '\n';
    return 0;
}