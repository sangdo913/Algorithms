#include<cstdio>
#include<cstring>

struct Info{
    int map[100][100], n;
    enum NS { N = 1, S = 2};

    void init()
    {
        scanf("%d\n", &n);
        for(int i = 0; i < n; i++)
        {
            for(int j = 0; j < n; j++)
            {
                scanf("%d \n", & map[i][j]);
            }
        }
    }

    int count()
    {
        int res = 0, prevMag = N;
        for(int j = 0; j < n; j++)
        {
            prevMag = N;
            for(int i = 0; i < n; i++)
            {
                res += (map[i][j] != prevMag) && (map[i][j] == S);
                if(map[i][j]) prevMag = map[i][j];
            }
        }
        return res;
    }

    void remove()
    {
        for(int j = 0 ; j < n; j++)
        {
            for(int i = 0; i < n; i++)
            {
                if(map[i][j] == S)
                {
                    map[i][j] = 0;
                }
                else if (map[i][j] == N)
                    break;
            }
        }
        for(int j = 0 ; j < n; j++)
        {
            for(int i = n - 1; i >= 0; i--)
            {
                if(map[i][j] == N)
                {
                    map[i][j] = 0;
                }
                else if(map[i][j] == S) break;
            }
        }
    }
} info;

int Magnetic()
{
    for(int tc = 1; tc <= 10; tc++)
    {
        info.init();
        info.remove();
        printf("#%d %d\n", tc, info.count());
    }
    return 0;
}