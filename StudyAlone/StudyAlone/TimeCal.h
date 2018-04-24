#include<iostream>

using namespace std;

int TimeCal()
{
    int t;
    cin >> t;
    
    for(int tc = 1; tc <= t; tc++)
    {
       int time1, time2, h, m;
        cin >> h >> m;
        time1 = h*60 + m;
        cin >> h >> m;
        time2 = h*60 + m;

        int resTime = time1 + time2;
        h = (resTime / 60)% 12;
        h = h == 0 ? 12 : h;
        cout <<  '#' << tc << ' ' << h << ' ' << resTime % 60 << '\n';
    }
    return 0;
}