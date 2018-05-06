#include<stdio.h>
#include<string.h>

struct SangHo
{
    char map[22][22];
    enum wallType {SWALL = '#', WALL = '*', WATER = '-', UP = '^', DOWN = 'v', LEFT = '<', RIGHT = '>'};
    enum DIRECT {U = 0, D = 1, L = 2, R = 3, S = 4};
    int conv[255];

    const int dr[5] = {-1,1,0,0,0};
    const int dc[5] = {0,0,-1,1,0};
    int w, h, n, r ,c, direct;
    void init()
    {
        memset(map,SWALL, sizeof(map));
        scanf("%d %d\n", &h, &w);
        for(int i = 1; i <= h; i++)
        {
            for(int j = 1; j <= w; j++)
            {
                scanf("%c\n ", &map[i][j]);
                if(map[i][j] == UP || map[i][j] == DOWN || map[i][j] == LEFT || map[i][j] == RIGHT)
                {
                    r = i; c = j;
                    direct = conv[map[i][j]];
                }
            }
        }
    }

    void print()
    {
        for(int i = 1; i <= h; i++)
        {
            for(int j = 1; j <= w; j++)
            {
                printf("%c", map[i][j]);
            }

            printf("\n");
        }
    }
    void shoot(int r, int c, int direct)
    {
        int nextR = r + dr[direct], nextC = c + dc[direct];
        while(map[nextR][nextC] != WALL && map[nextR][nextC] != SWALL)
        {
            nextR += dr[direct];
            nextC += dc[direct];
        }

        if(map[nextR][nextC] == WALL) map[nextR][nextC] = '.';
    }

    void comm()
    {
        scanf("%d\n", &n);
        char comm;
        while(n--)
        {
            scanf("%c", &comm);

            if(comm == 'S')
            {  
                shoot(r, c, direct);
            }         
            else
            {
                direct = conv[comm];
            }

            int nextR = r + dr[conv[comm]];
            int nextC = c + dc[conv[comm]];

            if(map[nextR][nextC] == '.')
            {
                map[r][c] = '.';
                r = nextR;
                c = nextC;
            }

            map[r][c] = conv[direct];
        }
    }

    void setComm()
    {
        conv['U'] = U;
        conv['D'] = D;
        conv['R'] = R;
        conv['L'] = L;
        conv['S'] = S;
        conv[UP] = U;
        conv[LEFT] = L;
        conv[RIGHT] = R;
        conv[DOWN] = D;
        conv[U] = '^';
        conv[D] = 'v';
        conv[L] = '<';
        conv[R] = '>';
    }
} info;

int SangHoBattleField()
{
    int t;
    scanf("%d\n", &t);
    info.setComm();

    for(int tc = 1; tc <= t; tc++)
    {
        printf("#%d ", tc);
        info.init();
        info.comm();
        info.print();
    }

    return 0;
}