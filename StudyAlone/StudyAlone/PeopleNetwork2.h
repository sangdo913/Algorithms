#include<cstdio>

struct NetworkInfo
{
    int map[1000][1000], size;

    void init()
    {
        scanf("%d ", &size);
        for(int i = 0; i < size; i++)
        {
            for(int j = 0; j < size; j++)
            {
                scanf("%d ", &map[i][j]);
                if(map[i][j] == 0) map[i][j] = 100000;
            }
        }
    }

    int getMin(int i1, int i2)
    {
        return i1 < i2 ? i1 : i2;
    }
        
    int getRes()
    {
        for(int k = 0; k < size; k++)
        {
            for(int i = 0; i < size; i++)
            {
                for(int j = 0; j < size; j++)
                {
                    map[i][j] = getMin(map[i][k] + map[k][j], map[i][j]);
                }
            }
        }
        int res[1000] = {0};
        int min = 987654321;
        for(int i = 0; i < size; i++)
        {
            for(int j = 0; j < size; j++)
            {
                if(i != j) res[i] += map[i][j];
            }
            min = getMin(min, res[i]);
        }
        return min;
    }
} info;

int PeopleNetwork2()
{
    int t;
    scanf("%d\n", &t);
    for(int tc = 1; tc <= t; tc++)
    {
        info.init();
        printf("#%d %d\n", tc, info.getRes());
    }
    return 0;
}