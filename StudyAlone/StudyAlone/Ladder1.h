#include<cstdio>
#include<cstring>

struct LadderInfo
{
    char ladder[102][102];
    const int dr[3] = {-1,0,0};
    const int dc[3] = {0,-1,1};
    int st;

    void initLadder()
    {
        memset(ladder, 0, sizeof(ladder));
    }
    void init()
    {
        int t;
        scanf("%d\n", &t);

        for(int i = 1; i <= 100; i++)
        {
            for(int j = 1; j <= 100; j++)
            {
                scanf("%c \n", &ladder[i][j]);
                if(ladder[i][j] == '2') st = j;
            }
        }
    }

    int goal()
    {
        typedef enum DIR {UP = 0, LEFT = 1, RIGHT = 2} DIR;

        int direct = UP;
        int r = 100;
        int c = st;

        while(r != 1)
        {
            if(direct == UP)
            {
                if(ladder[r][c - 1] == '1') direct = LEFT;
                else if(ladder[r][c + 1] == '1') direct = RIGHT;
            }

            else
            {
                if(ladder[r][c + dc[direct]] != '1') direct = UP;
            }

            r += dr[direct]; c += dc[direct];
        }

        return c - 1;
    }
} info;

int Ladder1()
{
    int t = 10;
    info.initLadder();

    for(int tc = 1; tc <= 10; tc++)
    {
        info.init();
        printf("#%d %d\n", tc, info.goal());    
    }
}