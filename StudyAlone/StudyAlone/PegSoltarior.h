#include<iostream>
#include<cstdio>
#include<cstring>

using namespace std;

struct PinInfo
{
    char map[102][102];
    int pinInfo[102][102];
    int n, pinNum, remains, minRemain, minMove;
    const int dr[4] = {-1,1,0,0};
    const int dc[4] = {0,0,-1,1};

    typedef struct Pin{int r, c; bool deleted;} pin;
    pin pins[8];

    void init()
    {
        int n = 5; int m = 9;
        memset(map,'#',sizeof(map));
        pinNum = 0;
        minRemain = 8;
        minMove = 10000;

        for(int i = 1; i <= n; i++)
        {
            for(int j = 1; j  <= m; j++)
            {
                scanf("%c \n",&map[i][j]);
                if(map[i][j] == 'o')
                {
                    pinInfo[i][j] = pinNum;
                    pins[pinNum].r = i;
                    pins[pinNum].c = j;
                    pins[pinNum++].deleted = false;
                }
            }
        }
        remains = pinNum;
    }
    bool moveCheck()
    {
        for(int i = 0 ; i < pinNum; i++)
        {
            if(pins[i].deleted) continue;

            for(int d = 0; d < 4; d++)
            {
                int nextR = pins[i].r + dr[d];
                int nextC = pins[i].c + dc[d];
                if(map[nextR][nextC] == 'o' && map[nextR + dr[d]][nextC + dc[d]] == '.') return true;
            }
        }
        return false;
    }

    int getMin(int i1, int i2)
    {
        return i1 < i2 ? i1 : i2;
    }

    void deletePin(int move)
    {
        if(!moveCheck())
        {
            if (remains < minRemain)
            {
                minRemain = remains;
                minMove = move;
            }
            return;
        }

        int nextR, nextC,delNum;
        pin temp;
        
        for(int i = 0 ; i < pinNum; i++)
        {
            if(pins[i].deleted) continue;

            for(int d = 0 ; d < 4; d ++)
            {
                nextR = pins[i].r + dr[d]; nextC = pins[i].c + dc[d];
                if(map[nextR][nextC] == 'o' && map[nextR + dr[d]][nextC + dc[d]] == '.')
                {
                    delNum = pinInfo[nextR][nextC];
                    map[nextR][nextC] = '.';

                    map[pins[i].r][pins[i].c] = '.';

                    temp = pins[i];

                    pins[i].r = nextR + dr[d]; pins[i].c = nextC + dc[d];
                    pins[delNum].deleted = true;

                    map[pins[i].r][pins[i].c] = 'o';
                    pinInfo[pins[i].r][pins[i].c] = i;

                    remains--;

                    deletePin(move + 1);

                    pinInfo[nextR][nextC] = delNum;
                    map[nextR][nextC] = 'o';

                    map[pins[i].r][pins[i].c] = '.';

                    pins[i] = temp;

                    pins[delNum].deleted = false;

                    map[pins[i].r][pins[i].c] = 'o';
                    pinInfo[pins[i].r][pins[i].c] = i;

                    remains++;
                } 
            }
        }
    }

} info;

int PagSoltarior()
{
    int n;
    scanf("%d\n",&n);
    while(n--)
    {
        info.init();
        info.deletePin(0);
        printf("%d %d\n", info.minRemain, info.pinNum - info.minRemain);
    }
    
    return 0;
}
