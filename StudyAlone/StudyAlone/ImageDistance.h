#include<cstdio>
#include<cstring>

struct ImageDistance
{
    char x[502];
    char y[502];
    int distance[501][501];
    int size;

    void init()
    {
        scanf("%d\n", &size);
        memset(distance, 0, sizeof(distance));
        scanf("%s\n", x + 1);
        scanf("%s\n", y + 1);
    }

    int getMax(int i1, int i2)
    {
        return i1 > i2 ? i1 : i2;
    }

    float getDistance()
    {
        for(int i = 1; i <= size; i++)
        {
            for(int j = 1; j <= size; j++)
            {
                if(x[i] == y[j])
                {
                    distance[i][j] = distance[i - 1][j - 1] + 1;

                }
                else
                {
                    distance[i][j] = getMax(distance[i - 1][j], distance[i][j - 1]);
                }
            }
        }

        return (float)distance[size][size] / (float) size * 100.f;    
    }
} info;

int ImageDistance()
{
    int t;
    scanf("%d\n", &t);

    for(int tc = 1; tc <= t; tc++)
    {
        info.init();
        printf("#%d %.2f\n", tc, info.getDistance());
    }
    return 0;
}