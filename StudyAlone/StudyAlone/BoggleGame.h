#include<stdio.h>
#include<string.h>

struct BoggleGameInfo
{
   bool check[11][7][7];
    char map[7][7];
    char str[11];
    int len;
    const char res[2][4] = {"NO", "YES"};
    const int dr[8] = {-1, -1, -1, 0, 0, 1, 1, 1};
    const int dc[8] = {-1, 0, 1, -1, 1, -1, 0, 1};
    
    void init()
    {
        memset(map, 0, sizeof(map));
        
        for(int i = 1; i < 6; i++)
        {
            for(int j = 1; j < 6; j++)
            {
               scanf("%c \n", &map[i][j]);
            }
        }
    }

    void print()
    {
        int n;
        scanf("%d\n", &n);

        while(n--)
        {
            memset(check, false, sizeof(check));

             scanf("%s\n", str);
             len = getNum(str);

            printf("%s %s\n", str, res[getRes()]);
        }
    }

    bool find(int r, int c, int h)
    {
        if(h == len) return true;

        int nextR = r , nextC = c;

        int d;
        for(d = 0; d < 8; d++)
        {
           nextR = r + dr[d];
           nextC = c + dc[d];

           if(check[h][nextR][nextC]) continue;
            check[h][nextR][nextC] = true;

           if(map[nextR][nextC] == str[h])
           {
               if( find(nextR, nextC, h + 1))
               {
                    return true;
               }
           }
        }

        return false;
    }

    bool getRes()
    {
        for(int i = 1; i < 6; i++)
        {
            for(int j = 1; j < 6; j++)
            {
                if(map[i][j] == str[0])
                {
                    if(find(i, j, 1))
                    {
                        return true;
                    }
                }
            }
        }
        return false;
    }
    
    int getNum(char *str)
    {
        int i = 0;
        while(str[i])
        {
            i++;    
        }
        return i;
    }
}info;



int BoggleGame()
{
    int t;
    scanf("%d\n", &t);
    
    while(t--)
    {
        info.init();
        info.print();
    }


    return 0;
}
