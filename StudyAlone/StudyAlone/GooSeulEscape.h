#include<iostream>
#include<cstdio>
#include<cstring>

using namespace std;

struct Info
{
    typedef struct { int r; int c;} Cod;
    int n,m;
    char map[10][10];
    const int dr[4] = {-1,1,0,0};
    const int dc[4] = {0,0,-1,1};
    const int reverse[4] = {1,0,3,2};
    typedef enum {RED = 0, BLUE} type;

    Cod pos[2];

    int min;
    void init()
    {
        min = 11;
        scanf("%d %d\n", &n, &m);
        memset(map, '#', sizeof(map));
        
        for(int r = 0; r < n; r++)
        {
            for(int c = 0; c < m; c++)
            {
                scanf("%c", &map[r][c]);
                if(map[r][c] == 'B')
                {
                    pos[BLUE].r = r;
                    pos[BLUE].c = c;
                    map[r][c] = '.';
                }
                else if(map[r][c] == 'R')
                {
                    pos[RED].r = r;
                    pos[RED].c = c;
                    map[r][c] = '.';
                }
            }
            scanf("\n");
        }
    }

    void roll(Cod red, Cod blue, int cnt, int from)
    {
        if(from != -1)
        {
            from = reverse[from];
        }

        if(cnt > min)
        {
            return ;
        }

        int tRed = 0, tBlue = 0;
        Cod next, nRed, nBlue;

        for(int d = 0 ; d < 4; d++)
        {
            if(from == d) continue;
            nBlue.r = blue.r; nBlue.c = blue.c; nRed.r = red.r; nRed.c = red.c;

            tRed = tBlue = 0;

            next.r = nRed.r + dr[d];
            next.c = nRed.c + dc[d];
            
            bool arriveRed = false;
            bool arriveBlue = false;

            while(map[next.r][next.c] != '#')
            {
                nRed.r = next.r; nRed.c = next.c;
                if(map[next.r][next.c] == 'O')
                {
                    arriveRed = true; break;
                }
                tRed++; 
                next.r += dr[d];
                next.c += dc[d];
            }
            
            next.r = nBlue.r + dr[d];
            next.c = nBlue.c + dc[d];

            while(map[next.r][next.c] != '#')
            {
                nBlue.r = next.r; nBlue.c = next.c;
                if(map[next.r][next.c] == 'O')
                {
                    arriveBlue = true; break;
                }

                tBlue++;
                next.r += dr[d];
                next.c += dc[d];
            }

            if(arriveBlue) continue;

            else if(arriveRed) 
            {
                min = min < cnt + 1 ? min : cnt + 1;
                return;
            }

            if(nRed.r == nBlue.r && nBlue.c == nRed.c)
            {
                if(tRed < tBlue)
                {
                    nBlue.r -= dr[d];
                    nBlue.c -= dc[d];
                }
                else
                {
                    nRed.r -= dr[d];
                    nRed.c -= dc[d];
                }
            }

            roll(nRed, nBlue, cnt+1, d);
        }
    }
} info;

int GooSeulEscape()
{
    info.init();
    info.roll(info.pos[0], info.pos[1], 0,-1);

    printf("%d\n", info.min == 11 ? -1 : info.min);
    return 0;
}