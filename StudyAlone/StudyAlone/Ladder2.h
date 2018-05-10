#include<cstdio>
#include<cstring>

struct LadderInfo
{
    char ladder[102][102];
    const int dr[3] = {1,0,0};
    const int dc[3] = {0,-1,1};

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
            }
        }
    }

    int shortest()
    {
        int min = 10000;
        int minIndex, length;

        for(int i = 1; i <= 100; i++)
        {
            if(ladder[1][i] == '1')
            {
                length = goal(i);
                if(min >= length)
                {
                    minIndex = i - 1;
                    min = length;           
                }
            }    
        }
        return minIndex;
    }

    int goal(int st)
    {
        typedef enum DIR {DOWN = 0, LEFT = 1, RIGHT = 2} DIR;

        int direct = DOWN;
        int r = 1;
        int c = st, cnt = 0;;

        while(r != 100)
        {
            if(direct == DOWN)
            {
                if(ladder[r][c - 1] == '1') direct = LEFT;
                else if(ladder[r][c + 1] == '1') direct = RIGHT;
            }

            else
            {
                if(ladder[r][c + dc[direct]] != '1') direct = DOWN;
            }

            r += dr[direct]; c += dc[direct];
            cnt++;
        }

        return cnt;
    }
} info;

int ladder2()
{
    int t = 10;
    info.initLadder();

    for(int tc = 1; tc <= 10; tc++)
    {
        info.init();
        printf("#%d %d\n", tc, info.shortest());    
    }
}