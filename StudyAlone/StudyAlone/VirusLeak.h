#include<iostream>
#include<cstring>
#include<queue>
#include<cstdio>

using namespace std;

struct VirusLeak_Info
{
    int map[10][10];
    int tempMap[10][10];

    typedef struct cod {int r; int c;} c;

    int n, m;
    int max;
    const int dr[4] = {-1,1,0,0};
    const int dc[4] = {0,0,-1,1};
    int getMax(int i1, int i2)
    {
        return i1 < i2 ? i2 : i1;
    }

    void init()
    {
        int max = 0;
        scanf("%d %d\n", &n, &m);

        memset(map, -1, sizeof(map));

        for(int r = 1; r <= n; r++)
        {
            for(int c = 1; c <= m; c++)
            {
                scanf("%d", &map[r][c]);
            }
        }
    }

    void extension()
    {
        c now, next;
        
        memcpy(tempMap, map, sizeof(map));

        queue<c> que;
        for(int r = 1; r <= n; r++)
            for(int c = 1; c <= m; c++)
            {
                if(tempMap[r][c] == 2)
                {
                    now.r = r;
                    now.c = c;
                    que.push(now);
                }    
            }

        while(que.size())
        {
            now = que.front();
            que.pop();

            for(int d = 0; d < 4; d++)
            {
                next.r = now.r + dr[d];
                next.c = now.c + dc[d];
                if(tempMap[next.r][next.c] == 0)
                {
                    que.push(next);
                    tempMap[next.r][next.c] = 2;
                }
            }
        }
    }

    int getZeros()
    {
        int cnt = 0;
        for(int r = 1; r <= n; r++)
            for(int c = 1; c <= m; c++)
                cnt = tempMap[r][c] == 0 ? ++cnt : cnt;

        return cnt;
    }

    void makeWall(int r, int c, int wallCnt)
    {
        if(wallCnt == 3)
        {
            extension();
            max = getMax(getZeros(),max);
            return ;
        }

        if(map[r][c] == -1) return;

        int nextR, nextC;
        if(c != m)
        {
            nextC = c + 1;
            nextR = r;
        }
        else
        {
            nextC = 1;
            nextR = r + 1;
        }

        if(map[r][c] == 0)
        {   
            map[r][c] = 1;
            makeWall(nextR,nextC, wallCnt + 1);
            map[r][c] = 0;
        }

        makeWall(nextR, nextC, wallCnt);
    }
}info;

int VirusLeak()
{
    info.init();
    info.makeWall(1,1,0);
    int res = info.max;

    printf("%d\n", res);
    return 0;
}