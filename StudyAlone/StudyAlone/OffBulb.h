#include<iostream>
#include<cstring>
#include<cstdio>

using namespace std;

struct OffBulb_Info
{
    int map[20][20];
    int tempMap[20][20];
    bool turnOn[20][20];
    int min;

    int n;
    const int dr[5] = {-1,1,0,0,0};
    const int dc[5] = {0,0,-1,1,0};

    void click(int r, int c)
    {
        int nextR, nextC;

        for(int d = 0 ; d < 5; d++)
        {
            nextR = r + dr[d];
            nextC = c + dc[d];

            if(tempMap[nextR][nextC] == -1) continue;
            tempMap[nextR][nextC] ^= 1;
        }
    }

    int getMin(int cnt)
    {    
        for(int r = 2; r <= n; r++)
        {
            for(int c = 1; c <= n; c++)
            {
                if(tempMap[r-1][c]) 
                {
                    cnt++;
                    click(r,c);
                }
            }
        }

        for(int c = 1; c <= n; c++)
        {
            if(tempMap[n][c]) return -1;
        }

        return cnt;
    }

    int getNum(int n)
    {
        int res = 0;
        while(n)
        {
            res = n&1 ? ++res : res;
            n >>= 1;
        }
        return res;
    }

    void setFirst(int d)
    {
        int c = 1;
        memcpy(tempMap,map,sizeof(map));

        while(d)
        {
            if(d&1) click(1,c);
            d >>= 1;
            c++;
        }
    }

    void init()
    {
        scanf("%d", &n);
        memset(map,-1,sizeof(map));
        memset(turnOn, false, sizeof(turnOn));
        min = 500;
        for(int r = 1 ; r <= n; r++)
            for(int c = 1; c <= n; c++)
                scanf("%d", &map[r][c]);
    }
}info;

int OffBulb()
{
    info.init();
    int res;
    int min = 500;
    for(int i = 0 ; i < (1 << info.n); i++)
    {
        int cnt = info.getNum(i);
        info.setFirst(i);
        res = info.getMin(cnt);
        if(res != -1) 
        {
            min = min > res ? res : min;
        }
    }

    printf("%d\n", min == 500 ? -1 : min);
    return 0;
}