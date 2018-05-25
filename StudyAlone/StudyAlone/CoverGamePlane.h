#include<stdio.h>
#include<string.h>

struct GameInfo
{
    int h, w, res;

    char map[22][22];
    const bool blocks [4][4] = { {1,1,0,1}, {1,1,1,0}, {1,0,1,1}, {0,1,1,1} };
    const int dr[4] = {0,0,1,1};
    const int dc[4] = {0,1,0,1};

    void findMap(char map[22][22], int r, int c)
    {
       char cpyMap[22][22];

       if(r == h + 1)
       {
           for(int i = 1; i <= h; i++)
           {
               for(int j = 1; j <= w; j++)
               {
                   if(map[i][j] == '.') return;
               }
           }
           res ++; return;
       }

       memcpy(cpyMap, map, sizeof(cpyMap));

        int nextR = r, nextC = c + 1;

        if(nextC > w)
        {
            nextR++;
            nextC = 1;
        }

        if(cpyMap[r][c] == '.')
        {
           for(int i = 0; i < 3; i++)
           {
                bool check = true;

                for(int d = 0; d < 4; d++)
                {
                    int cR = r + dr[d]; int cC = c + dc[d];

                    if(cpyMap[cR][cC] == '#' && blocks[i][d] == 1) 
                    {
                        check = false;
                        break;
                    }
                }

                if(check)
                {
                    for(int k = 0; k < 4; k++)
                    {
                        if(blocks[i][k]) cpyMap[r + dr[k]][c + dc[k]] = '#'; 
                    }

                    findMap(cpyMap, nextR, nextC);

                    for(int k = 0; k < 4; k++)
                    {
                        if(blocks[i][k]) cpyMap[r + dr[k]][c + dc[k]] = '.';
                    }
                }
            }
        }

       else if(cpyMap[r][c] == '#')
       {
           bool check = true;

            for(int d = 0; d < 4; d++)
            {
                int cR = r + dr[d]; int cC = c + dc[d];

                if(cpyMap[cR][cC] == '#' && blocks[3][d] == 1) 
                {
                    check = false;
                    break;
                }
            }

            if(check)
            {
                for(int k = 0; k < 4; k++)
                {
                    if(blocks[3][k]) cpyMap[r + dr[k]][c + dc[k]] = '#'; 
                }

                findMap(cpyMap, nextR, nextC);

                for(int k = 0; k < 4; k++)
                {
                    if(blocks[3][k]) cpyMap[r + dr[k]][c + dc[k]] = '.';
                }
            }
            findMap(cpyMap, nextR,nextC);
       }
    }

        void init()
        {
            res = 0;
            scanf("%d %d\n", &h, &w);
            
            memset(map, '#', sizeof(map));
            
            for(int i = 1; i <= h; i++)
            {
                for(int j = 1; j <= w; j++)
                {
                    scanf("%c \n", &map[i][j]);
                }
            }
        }
    } info;

    int CoverGamePlane()
{
    int t;
    scanf("%d\n", &t);

    while(t--)
    {
        info.init();
        info.findMap(info.map, 1, 1);
        printf("%d\n", info.res);
    }
    return 0;
}
