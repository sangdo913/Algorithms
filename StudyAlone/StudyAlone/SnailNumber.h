#include<cstring>
#include<cstdio>

using namespace std;

struct SnailInfo
{
    const int dr[4] = {-1,1,0,0};
    const int dc[4] = {0,0,-1,1};
    const int next[4] = {3,2,0,1};

    int n;
    int map[11][12][12];

    void init()
    {
        memset(map,-1,sizeof(map));

        for(int n = 1; n < 11; n++)
        {
            for(int i = 1; i <= n; i++)
            {
                for(int j = 1; j <= n; j++)
                {
                    map[n][i][j] = 0;
                }
            }

            
            int cnt = 1;
            int max = n*n;
            int r = 1, c = 1;
            int direct = 3;

            while(cnt <= max)
            {
                map[n][r][c] = cnt++;
                int nextR = r + dr[direct];
                int nextC = c + dc[direct];
                if(map[n][nextR][nextC])
                {
                    direct = next[direct];
                }
                r += dr[direct];
                c += dc[direct];
            }    
        }
    }

    void getMap(int num)
    {
        for(int i = 1; i <= num; i++)
        {
            for(int j = 1; j <= num; j++)
            {
                printf("%d ", map[num][i][j]);
            }
            printf("\n");
        }       
    }
} info;

int SnailNumber()
{
    int t;
    scanf("%d\n", &t);
    info.init();

    for(int tc = 1; tc <= t; tc++)
    {
        int n;
        printf("#%d\n", tc);
        scanf("%d\n", &n);

        info.getMap(n);
    }
    return 0;
}