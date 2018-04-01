#include<iostream>
#include<cstdio>
#include<string.h>

using namespace std;

struct MakeWalkRoad_Info
{
    int map[10][10];
    int n;
    int k;
    int highst[5][2];
    int numOfHighst;
    int height;
    const int dr[4] = {-1,1,0,0};
    const int dc[4] = {0,0,-1,1};
    void init()
    {
        scanf("%d %d\n", &n, &k);
        for(int i = 0 ; i <= n + 1 ;i++)
        {
            for(int j = 0 ; j <= n + 1; j++) map[i][j] = 10000;
        }
        numOfHighst = 0;
        height = 0;

        for(int i = 1; i <= n; i++)
        {
            for(int j = 1; j <= n; j++)
            {
                scanf("%d", &map[i][j]);
                if(height < map[i][j])
                {
                    height = map[i][j];
                    numOfHighst = 0;
                    highst[numOfHighst][0] = i;
                    highst[numOfHighst++][1] = j;
                }
                else if (height == map[i][j])
                {
                    highst[numOfHighst][0] = i;
                    highst[numOfHighst++][1] = j;
                }
            }
        }
    }

    int max (int i1, int i2)
    {
        return i1 > i2 ? i1 : i2;
    }

    int maxLength(int r, int c, bool dig)
    {
        int length = 0;
        for(int d = 0; d < 4; d++)
        {
            int nextR = r + dr[d];
            int nextC = c + dc[d];
            int prev = map[r][c];

            if(map[r][c] > map[nextR][nextC])
            {
                map[r][c] = 1000;
                length = max(length,maxLength(nextR,nextC,dig));
                map[r][c] = prev;
            }
            else if(dig)
            {   
                for(int i = 1 ; i <= k; i++)
                {
                    if(map[r][c] > map[nextR][nextC] - i) 
                    {
                        map[r][c] = 1000;
                        map[nextR][nextC] -= i;
                        length = max(length,maxLength(nextR,nextC,false));
                        map[nextR][nextC] += i;
                        map[r][c] = prev;
                    }
                }
            }
        }
        return length+1;
    }
} MakeWalkRoad_info;

int MakeWalkRoad()
{
    int t;
    scanf("%d",&t);
    MakeWalkRoad_Info& info = MakeWalkRoad_info;
    for(int tc = 1; tc <= t; tc++)
    {
        int res = 0;
        MakeWalkRoad_info.init();
        for(int i = 0 ; i<MakeWalkRoad_info.numOfHighst; i++)
        {
            res = info.max(res,info.maxLength(info.highst[i][0], info.highst[i][1],true));
        }

        printf("#%d %d\n", tc, res);
    }
    return 0;
}