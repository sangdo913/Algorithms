#include<iostream>
#include<cstring>

using namespace std;

struct Info
{
    int map [6][6];
    bool constructed[9999999];
    const int dr[4] = {-1,1,0,0};
    const int dc[4] = {0,0,-1,1};
    int pan[7];
    int atoi(int str[7])
    {
        int res = 0;
        for(int i = 0; i < 7; i++)
        {
            res *= 10;
            res += str[i];
        }
        return res;
    }
    int res;

    void make(int r, int c, int cnt)
    {
        if(cnt == 6)
        {
            pan[6] = map[r][c];
            res += !constructed[atoi(pan)];
            constructed[atoi(pan)] = true;
            return;
        }

        int nextR, nextC;
        pan[cnt] = map[r][c];

        for(int d = 0; d < 4; d++)
        {
            nextR = r + dr[d];
            nextC = c + dc[d];
            if(map[nextR][nextC] == -1) continue;
            make(nextR,nextC,cnt+1);
        }

        return;
    }
    void init()
    {
        memset(constructed,false,sizeof(constructed));
        memset(pan,0,sizeof(pan));
        memset(map,-1,sizeof(map));
        res = 0;
        for(int r = 1; r <=4; r++)
        {
            for(int c = 1; c <= 4; c++)
            {
                cin >> map[r][c];
            }
        }
    }
} info;

int NumberContact()
{
    int t;
    cin >> t;
    for(int tc = 1; tc <= t; tc++)
    {
        info.init();
        for(int r = 1; r <= 4; r++)
        {
            for(int c = 1; c <= 4; c++)
                info.make(r,c,0);
        }

        cout << '#'<< tc << ' ' << info.res << '\n';
    }
    return 0;
}